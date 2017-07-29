#include "window.h"

_Window *_window;

_Window::_Window(QPrinter *printer, QWidget *parent) :
    QWidget(parent),
    masterLayout(new QGridLayout(this)),
    tabs(new Tabs(this)),
    root(new Root(this)),
    preview(new Preview(printer, this)),
    controls(new Controls(this))
{
    /*
     * masterLayout
     * |-tabs
     * |-root -- preview
     * |-controls
     */
    QObject::connect(tabs->rootObject,
                     SIGNAL(tabBarIndexChanged(qint32)),
                     this,
                     SLOT(tabBarIndexChanged(qint32)));

    QObject::connect(root->rootObject,
                     SIGNAL(swipeViewIndexChanged(qint32)),
                     this,
                     SLOT(swipeViewIndexChanged(qint32)));

    QObject::connect(controls->rootObject,
                     SIGNAL(cancelButtonClicked()),
                     this,
                     SLOT(cancelButtonClicked()));

    QObject::connect(controls->rootObject,
                     SIGNAL(zoomSliderValueChanged(qreal)),
                     preview,
                     SLOT(setZoom(qreal)));

    QObject::connect(controls->rootObject,
                     SIGNAL(nextPageButtonClicked()),
                     preview,
                     SLOT(showNextPage()));

    QObject::connect(controls->rootObject,
                     SIGNAL(prevPageButtonClicked()),
                     preview,
                     SLOT(showPrevPage()));

    QObject* generalObject = root->rootObject->findChild<QObject*>("generalObject");

    QObject::connect(generalObject,
                     SIGNAL(newPrinterSelected(QString)),
                     this,
                     SLOT(newPrinterSelected(QString)));

    QObject::connect(generalObject,
                     SIGNAL(remotePrintersToggled(QString)),
                     this,
                     SLOT(remotePrintersToggled(QString)));

    tabs->setMinimumSize(700, 32);

    root->setMinimumSize(320, 408);

    preview->setMinimumSize(380, 408);

    controls->setMinimumSize(700, 40);

    masterLayout->setColumnMinimumWidth(0, 320);
    masterLayout->setColumnMinimumWidth(1, 380);
    masterLayout->setRowMinimumHeight(0, 32);
    masterLayout->setRowMinimumHeight(1, 408);
    masterLayout->setRowMinimumHeight(2, 40);
    masterLayout->setSpacing(0);
    masterLayout->setMargin(0);

    masterLayout->addWidget(tabs,     0, 0, 1, 2);
    masterLayout->addWidget(root,     1, 0, 1, 1);
    masterLayout->addWidget(preview,  1, 1, 1, 1);
    masterLayout->addWidget(controls, 2, 0, 1, 2);

    preview->widgetHeight = masterLayout->itemAt(1)->geometry().height();

    adjustSize();

    setMaximumSize(700, 480);
    setMinimumSize(700, 480);

    init_backend();
}

CPrintDialog::CPrintDialog(QPrinter* printer, QWidget *parent) :
    QAbstractPrintDialog(printer, parent)
{
    _window = new _Window(printer, parent);
    _window->show();
}

void _Window::tabBarIndexChanged(qint32 index) {
    root->rootObject->setProperty("index", index);
}

void _Window::swipeViewIndexChanged(qint32 index) {
    tabs->rootObject->setProperty("index", index);
}

void _Window::cancelButtonClicked() {
    exit(0);
}

static int add_printer_callback(PrinterObj *p) {
    //qDebug() << "Printer" << p->name << "added!";
    _window->addPrinter(p->name);
}

static int remove_printer_callback(char *printer_name) {
    qDebug() << "Printer" << printer_name << "removed!";
}

gpointer _Window::ui_add_printer(gpointer user_data) {
    /*
     * Need this delay so that the FrontendObj
     * initialization completes
    */
    bool* enabled = (bool*)user_data;
    for (int i = 0; i < 100000000; i++);
    Command cmd;
    if (*enabled)
        cmd.command = "unhide-remote-cups";
    else
        cmd.command = "hide-remote-cups";
    parse_commands(&cmd);
    clearPrinters();
    g_hash_table_foreach(f->printer, ui_add_printer_aux, NULL);
}

void ui_add_printer_aux(gpointer key, gpointer value, gpointer user_data) {
    _window->addPrinter((const char*)key);
}

void _Window::addPrinter(const char *printer) {
    QObject* obj = root->rootObject->findChild<QObject*>("generalObject");
    if (obj) {
        QMetaObject::invokeMethod(obj,
                                  "updateDestinationModel",
                                  Q_ARG(QVariant, printer));
    }
    else
        qDebug() << "generalObject Not Found";
}

gpointer _Window::parse_commands(gpointer user_data) {
    Command* cmd = (Command*)user_data;
    if (cmd->command.compare("hide-remote-cups") == 0)
        hide_remote_cups_printers(f);
    else if (cmd->command.compare("unhide-remote-cups") == 0)
        unhide_remote_cups_printers(f);
    else if (cmd->command.compare("get-all-options") == 0) {
        char printerName[300];
        strcpy(printerName, cmd->arg1.c_str());
        Options *options = get_all_printer_options(_window->f, printerName, "CUPS");
        for (int i = 0; i < options->count; i++) {
            GHashTableIter iterator;
            g_hash_table_iter_init(&iterator, options->table);
            GList *keys = g_hash_table_get_keys(options->table);
            qDebug() << (char *)keys->data;
//            for (int j = 0; j < options[0][i].num_supported; j++)
//                qDebug() << options[0][i].supported_values[j];
//            qDebug() << "-----------";
        }

    }
}

void _Window::init_backend() {
    event_callback add_cb = (event_callback)add_printer_callback;
    event_callback rem_cb = (event_callback)remove_printer_callback;
    f = get_new_FrontendObj(NULL, add_cb, rem_cb);
    //bool enabled = true;
    //g_thread_new("add_printer_thread", (GThreadFunc)ui_add_printer, &enabled);
    connect_to_dbus(f);
    //ui_add_printer(&enabled);
}

void _Window::clearPrinters() {
    QObject* obj = root->rootObject->findChild<QObject*>("generalObject");
    if (obj) {
        QMetaObject::invokeMethod(obj,
                                  "clearDestinationModel");
    }
    else
        qDebug() << "generalObject Not Found";
}

void _Window::newPrinterSelected(const QString &printer) {
    Command cmd;
    cmd.command = "get-all-options";
    cmd.arg1 = printer.toStdString();
    if (cmd.arg1.compare("") != 0)
        parse_commands(&cmd);
}

void _Window::remotePrintersToggled(const QString &enabled) {
    qDebug() << enabled;
}

void ui_add_job_hold_until(char *startJobOption) {}

void ui_add_maximum_print_copies(char *_copies) {}

void ui_add_pages_per_side(char *pages) {}

void ui_clear_supported_media() {}

void ui_add_supported_media(char *media) {}
