#include "commonprintdialog.h"
#include "preview.h"
#include <QGuiApplication>
#include <QQmlContext>
#include <QStringList>
#include <QQuickWidget>
#include <QDebug>
#include <QQmlComponent>
#include <string>
extern "C" {
#include "../backends/cups/src/print_frontend.h"
}

typedef struct {
    std::string command;
    std::string arg1;
    std::string arg2;
} Command;

gpointer ui_add_printer(gpointer user_data);
static void ui_add_printer_aux(const char* key, const char* value);

_CommonPrintDialog *_cpd;

CommonPrintDialog::CommonPrintDialog() {
    _cpd = new _CommonPrintDialog;
}

void CommonPrintDialog::exec() {
    QQuickWidget(&(_cpd->engine), Q_NULLPTR);
    _cpd->init_backend();
}

_CommonPrintDialog::_CommonPrintDialog() {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    engine.addImageProvider(QLatin1String("preview"), new QPdfPreview);
    engine.load(QUrl(QLatin1String("qrc:/app/main.qml")));
    QPreviewData data;

    BackendObject *bObj = new BackendObject();
    QObject* generalObject = engine.rootObjects().first()->findChild<QObject*>("generalObject");
    if (generalObject) {
        QObject::connect(generalObject,
                         SIGNAL(newPrinterSelected(QString)),
                         bObj,
                         SLOT(newPrinterSelected(QString)));

        QObject::connect(generalObject,
                         SIGNAL(remotePrintersToggled(QString)),
                         bObj,
                         SLOT(remotePrintersToggled(QString)));
    }
    else
        qDebug() << "generalObject Not Found";

    QObject* rootObject = engine.rootObjects().first()->findChild<QObject*>("rootObject");

    if (rootObject) {
        QObject::connect(rootObject,
                         SIGNAL(cancelButtonClicked()),
                         bObj,
                         SLOT(cancelButtonClicked()));
    }
    else
        qDebug() << "rootObject Not Found";
}
static int add_printer_callback(PrinterObj *p)
{
    printf("print_frontend.c : Printer %s added!\n", p->name);
}

static int remove_printer_callback(char *printer_name)
{
    printf("print_frontend.c : Printer %s removed!\n", printer_name);
}

void _CommonPrintDialog::init_backend() {
    event_callback add_cb = (event_callback)add_printer_callback;
    event_callback rem_cb = (event_callback)remove_printer_callback;

    _cpd->f = get_new_FrontendObj(NULL, add_cb, rem_cb);

    bool enabled = true;
    g_thread_new("add_printer_thread", ui_add_printer, &enabled);

    connect_to_dbus(_cpd->f);

    _cpd->loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(_cpd->loop);
}

gpointer parse_commands(gpointer user_data) {
    //for (int i = 0; i < 100000000; i++);
    Command* cmd = (Command*)user_data;

    if (cmd->command.compare("hide-remote-cups") == 0)
        hide_remote_cups_printers(_cpd->f);
    else if (cmd->command.compare("unhide-remote-cups") == 0)
        unhide_remote_cups_printers(_cpd->f);
    else if (cmd->command.compare("get-all-options") == 0) {
        char printerName[300];
        strcpy(printerName, cmd->arg1.c_str());
        get_all_printer_options(_cpd->f, printerName);
    }
}

void _CommonPrintDialog::addPrinter(const char *printer) {
    QObject* obj = _cpd->engine.rootObjects().first()->findChild<QObject*>("generalObject");
    if (obj) {
        QMetaObject::invokeMethod(obj,
                                  "updateDestinationModel",
                                  Q_ARG(QVariant, printer));
    }
    else
        qDebug() << "moreOptionsGeneral Not Found";
}

void _CommonPrintDialog::clearPrinters() {
    QObject* obj = _cpd->engine.rootObjects().first()->findChild<QObject*>("generalObject");
    if (obj) {
        QMetaObject::invokeMethod(obj,
                                  "clearDestinationModel");
    }
    else
        qDebug() << "moreOptionsGeneral Not Found";
}

gpointer ui_add_printer(gpointer user_data) {
    /*
     * Need this delay so that the FrontendObj
     * initialization completes
    */
    bool* enabled = (bool*)user_data;
    for (int i = 0; i < 100000000; i++);
    Command cmd;
    if (*enabled) {
        cmd.command = "unhide-remote-cups";
        parse_commands(&cmd);
    }
    else {
        cmd.command = "hide-remote-cups";
        parse_commands(&cmd);
    }
    _cpd->clearPrinters();
    g_hash_table_foreach(_cpd->f->printer, (GHFunc)ui_add_printer_aux, NULL);
}

static void ui_add_printer_aux(const char* key, const char* value) {
    _cpd->addPrinter(key);
}

void _CommonPrintDialog::addPrinterSupportedMedia(char *media) {
    QObject* obj = _cpd->engine.rootObjects().first()->findChild<QObject*>("generalObject");
    if (obj) {
        QMetaObject::invokeMethod(obj,
                                  "updatePaperSizeModel",
                                  Q_ARG(QVariant, media));
    }
    else
        qDebug() << "moreOptionsGeneral Not Found";
}

void _CommonPrintDialog::clearPrintersSupportedMedia() {
    QObject* obj = _cpd->engine.rootObjects().first()->findChild<QObject*>("generalObject");
    if (obj) {
        QMetaObject::invokeMethod(obj,
                                  "clearPaperSizeModel");
    }
    else
        qDebug() << "moreOptionsGeneral Not Found";
}

void ui_clear_supported_media() {
    _cpd->clearPrintersSupportedMedia();
}

void ui_add_supported_media(char *media) {
    _cpd->addPrinterSupportedMedia(media);
}

void _CommonPrintDialog::addMaximumPrintCopies(int copies) {
    QObject* obj = _cpd->engine.rootObjects().first()->findChild<QObject*>("generalObject");
    if (obj)
        obj->setProperty("maximumCopies", copies);
    else
        qDebug() << "MoreOptionsGeneral Not Found";
}

void ui_add_maximum_print_copies(char* _copies) {
    std::string copies(_copies);
    int delimiter = copies.find('-');
    int min = std::stoi(copies.substr(0, delimiter));
    int max = std::stoi(copies.substr(delimiter + 1));
    _cpd->addMaximumPrintCopies(max);
}

void _CommonPrintDialog::addJobHoldUntil(char *startJobOption) {
    QObject* obj = _cpd->engine.rootObjects().first()->findChild<QObject*>("jobsObject");
    if (obj) {
        QMetaObject::invokeMethod(obj,
                                  "updateStartJobsModel",
                                  Q_ARG(QVariant, startJobOption));
    }
    else
        qDebug() << "jobsObject Not Found";
}

void ui_add_job_hold_until(char *startJobOption) {
    _cpd->addJobHoldUntil(startJobOption);
}

void _CommonPrintDialog::addPagesPerSize(char *pages) {
    QObject* obj = _cpd->engine.rootObjects().first()->findChild<QObject*>("pageSetupObject");
    if (obj) {
        QMetaObject::invokeMethod(obj,
                                  "updatePagesPerSideModel",
                                  Q_ARG(QVariant, pages));
    }
    else
        qDebug() << "pageSetupObject Not Found";
}

void ui_add_pages_per_side(char *pages) {
    _cpd->addPagesPerSize(pages);
}

void _CommonPrintDialog::updateAllOptions(const QString &printer) {
    Command cmd;
    cmd.command = "get-all-options";
    cmd.arg1 = printer.toStdString();
    if (cmd.arg1.compare("") != 0) {
        parse_commands(&cmd);
    }
}

void BackendObject::newPrinterSelected(const QString &printer) {
    _cpd->updateAllOptions(printer);
}

void BackendObject::remotePrintersToggled(const QString _enabled) {
    bool enabled;
    /* Weird bug */
    if (_enabled.compare("true") == 0)
        enabled = false;
    else
        enabled = true;
    ui_add_printer(&enabled);
}

void BackendObject::cancelButtonClicked() {
    disconnect_from_dbus(_cpd->f);
    g_main_loop_quit(_cpd->loop);
    exit(0);
}
