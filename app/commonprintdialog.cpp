#include "commonprintdialog.h"
#include "preview.h"
#include <QGuiApplication>
#include <QQmlContext>
#include <QStringList>
#include <QQuickWidget>
#include <QDebug>
#include <QQmlComponent>
#include <QSpinBox>
#include <string>
extern "C" {
    #include "../backends/cups/src/print_frontend.h"
}

_CommonPrintDialog *_cpd;

CommonPrintDialog::CommonPrintDialog() {
    _cpd = new _CommonPrintDialog;
}

void CommonPrintDialog::exec() {
    //QQuickWidget(&(_cpd->engine), Q_NULLPTR);
    _cpd->init_backend();
}

_CommonPrintDialog::_CommonPrintDialog() {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    engine.addImageProvider(QLatin1String("preview"), new QPdfPreview);
    engine.load(QUrl(QLatin1String("qrc:/app/main.qml")));
    QPreviewData data;
    //engine.rootContext()->setContextProperty("preview_data", &data);

    QObject* preview = engine.rootObjects().at(0)->findChild<QObject*>("generalPreview");

    if (preview)
        preview->setProperty("preview_data", QVariant::fromValue(&data));
    else
        qDebug() << "Error: Preview not found!!!!";

}

void _CommonPrintDialog::init_backend() {
    _cpd->f = get_new_FrontendObj(NULL);
    g_thread_new("parse_commands_thread", parse_commands, NULL);
    connect_to_dbus(_cpd->f);
    _cpd->loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(_cpd->loop);
}

gpointer parse_commands(gpointer user_data) {
    for (int i = 0; i < 100000000; i++);
    get_all_printer_options(_cpd->f, "4510DX");
    g_main_loop_quit(_cpd->loop);
}

void _CommonPrintDialog::addPrinter(char *printer) {
    QVariant arg = printer;
    QMetaObject::invokeMethod((_cpd->engine).rootObjects().at(0),
                              "updateDestinationModel",
                              Q_ARG(QVariant, arg));
}

void ui_add_printer(char* printer) {
    _cpd->addPrinter(printer);
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
