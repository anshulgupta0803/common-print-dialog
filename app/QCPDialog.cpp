#include "QCPDialog.h"
#include <QGridLayout>
#include <QQuickItem>
#include "components.h"
extern "C" {
#include <CPDFrontend.h>
}

namespace {
struct Command {
    std::string command;
    std::string arg1;
    std::string arg2;
};
}

QCPDialog::QCPDialog(QPrinter *printer, QWidget *parent) :
    QAbstractPrintDialog (printer, parent),
    tabs(new Tabs(this)),
    root(new Root(this)),
    preview(new Preview(printer, this)),
    controls(new Controls(this)),
    masterLayout(new QGridLayout(this))
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

    QObject *generalObject = root->rootObject->findChild<QObject *>("generalObject");

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

void QCPDialog::tabBarIndexChanged(qint32 index)
{
    root->rootObject->setProperty("index", index);
}

void QCPDialog::swipeViewIndexChanged(qint32 index)
{
    tabs->rootObject->setProperty("index", index);
}

void QCPDialog::cancelButtonClicked()
{
    disconnect_from_dbus(f);
    close();
}

static void add_printer_callback(PrinterObj *p)
{
    qDebug() << "Printer" << p->name << "added!";
}

static void remove_printer_callback(char *printer_name)
{
    qDebug() << "Printer" << printer_name << "removed!";
}

void QCPDialog::addPrinter(const char *printer)
{
    QObject *obj = root->rootObject->findChild<QObject *>("generalObject");
    if (obj) {
        QMetaObject::invokeMethod(obj,
                                  "updateDestinationModel",
                                  Q_ARG(QVariant, printer));
    } else {
        qDebug() << "generalObject Not Found";
    }
}

void QCPDialog::parse_commands(gpointer user_data)
{
    Command *cmd = (Command *)user_data;
    if (cmd->command.compare("hide-remote-cups") == 0)
        hide_remote_cups_printers(f);
    else if (cmd->command.compare("unhide-remote-cups") == 0)
        unhide_remote_cups_printers(f);
    else if (cmd->command.compare("get-all-options") == 0) {
        char printerName[300];
        strcpy(printerName, cmd->arg1.c_str());
        Options *options = get_all_printer_options(f, printerName, (char *)"CUPS");
        GHashTableIter iterator;
        g_hash_table_iter_init(&iterator, options->table);
        gpointer _key, _value;
        while (g_hash_table_iter_next(&iterator, &_key, &_value)) {
            char *key = (char *)_key;
            Option *value = (Option *)_value;
            if (strcmp(key, "media") == 0) {
                qDebug() << "123media";
            }
        }
    }
}

void QCPDialog::init_backend()
{
    event_callback add_cb = (event_callback)add_printer_callback;
    event_callback rem_cb = (event_callback)remove_printer_callback;
    f = get_new_FrontendObj(NULL, add_cb, rem_cb);
    connect_to_dbus(f);
}

void QCPDialog::clearPrinters()
{
    QObject *obj = root->rootObject->findChild<QObject *>("generalObject");
    if (obj) {
        QMetaObject::invokeMethod(obj,
                                  "clearDestinationModel");
    } else
        qDebug() << "generalObject Not Found";
}

void QCPDialog::newPrinterSelected(const QString &printer)
{
    QStringList list = printer.split('#');
    Options *options = get_all_printer_options(f, list[0].toLatin1().data(), list[1].toLatin1().data());
    qDebug() << "Total Options:" << options->count;
}

void QCPDialog::remotePrintersToggled(const QString &enabled)
{
    bool toggle = enabled.compare("true") == 0 ? true : false;
    Command cmd;
    cmd.command = toggle ? "unhide-remote-cups" : "hide-remote-cups";
    parse_commands(&cmd);
}

void ui_add_job_hold_until(char *startJobOption) {}

void ui_add_maximum_print_copies(char *_copies) {}

void ui_add_pages_per_side(char *pages) {}

void ui_clear_supported_media() {}

void ui_add_supported_media(char *media) {}

QString QCPDialog::information()
{
    QString str = "CPD Library";
    return str;
}
