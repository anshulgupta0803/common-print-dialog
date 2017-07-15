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
    QObject* moreOptionsGeneral = engine.rootObjects().first()->findChild<QObject*>("moreOptionsGeneralObjectName");
    QObject::connect(moreOptionsGeneral,
                     SIGNAL(newPrinterSelected(QString)),
                     bObj,
                     SLOT(updatePrinterSupportedMedia(QString)));

    QObject::connect(moreOptionsGeneral,
                     SIGNAL(remotePrintersToggled(QString)),
                     bObj,
                     SLOT(remotePrintersToggled(QString)));

            QObject* preview = engine.rootObjects().at(0)->findChild<QObject*>("generalPreview");

    if (preview)
        preview->setProperty("preview_data", QVariant::fromValue(&data));
    else
        qDebug() << "generalPreview Not Found";

}

void _CommonPrintDialog::init_backend() {
    _cpd->f = get_new_FrontendObj(NULL);

    Command cmd;
    cmd.command = "get-all-options";
    cmd.arg1 = "4510DX";//(char*)g_hash_table_get_keys(_cpd->f->printer)->data;
    //GThread* get_all_option_thread = g_thread_new("get-all-options", parse_commands, &cmd);
    //g_thread_join(get_all_option_thread);
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
    else if (cmd->command.compare("get-all-options") == 0)
        get_all_printer_options(_cpd->f, "X950");
}

void _CommonPrintDialog::addPrinter(const char *printer) {
    QVariant arg = printer;
    QObject* obj = _cpd->engine.rootObjects().first()->findChild<QObject*>("moreOptionsGeneralObjectName");
    if (obj) {
        QMetaObject::invokeMethod(obj,
                                  "updateDestinationModel",
                                  Q_ARG(QVariant, arg));
    }
    else
        qDebug() << "moreOptionsGeneral Not Found";
}

void _CommonPrintDialog::clearPrinters() {
    QObject* obj = _cpd->engine.rootObjects().first()->findChild<QObject*>("moreOptionsGeneralObjectName");
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
    for(int i = 0; i < 100000000; i++);
    Command cmd;
    if (*enabled) {
        cmd.command = "unhide-remote-cups";
        //g_thread_new("unhide-remote-cups", parse_commands, &cmd);
        parse_commands(&cmd);
    }
    else {
        cmd.command = "hide-remote-cups";
        //g_thread_new("hide-remote-cups", parse_commands, &cmd);
        parse_commands(&cmd);
    }
    _cpd->clearPrinters();
    g_hash_table_foreach(_cpd->f->printer, (GHFunc)ui_add_printer_aux, NULL);
}

static void ui_add_printer_aux(const char* key, const char* value) {
    _cpd->addPrinter(key);
}

void _CommonPrintDialog::addPrinterSupportedMedia(char *media) {
    QVariant arg = media;
    QMetaObject::invokeMethod((_cpd->engine).rootObjects().at(0),
                              "updatePaperSizeModel",
                              Q_ARG(QVariant, arg));
}

void ui_add_supported_media(char *media) {
    _cpd->addPrinterSupportedMedia(media);
}

void _CommonPrintDialog::addMaximumPrintCopies(int copies) {
    QObject* obj = _cpd->engine.rootObjects().first()->findChild<QObject*>("moreOptionsGeneralObjectName");
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
    QObject* obj = _cpd->engine.rootObjects().first()->findChild<QObject*>("moreOptionsJobsObjectName");
    if (obj) {
        QMetaObject::invokeMethod(obj,
                                  "updateStartJobsModel",
                                  Q_ARG(QVariant, startJobOption));
    }
    else
        qDebug() << "MoreOptionsJobs Not Found";
}

void ui_add_job_hold_until(char *startJobOption) {
    _cpd->addJobHoldUntil(startJobOption);
}

void _CommonPrintDialog::addPagesPerSize(char *pages) {
    QObject* obj = _cpd->engine.rootObjects().first()->findChild<QObject*>("moreOptionsPageSetupObjectName");
    if (obj) {
        QMetaObject::invokeMethod(obj,
                                  "updatePagesPerSideModel",
                                  Q_ARG(QVariant, pages));
    }
    else
        qDebug() << "MoreOptionsPageSetup Not Found";
}

void ui_add_pages_per_side(char *pages) {
    _cpd->addPagesPerSize(pages);
}

void _CommonPrintDialog::test(const QString &msg) {
    qDebug() << msg;
    //TODO: Create a thread which will update printer specfic options
}

void BackendObject::updatePrinterSupportedMedia(const QString &msg) {
    _cpd->test(msg);
}

void BackendObject::remotePrintersToggled(const QString _enabled) {
    bool enabled;
    if (_enabled.compare("true") == 0)
        enabled = false;
    else
        enabled = true;
    ui_add_printer(&enabled);
}
