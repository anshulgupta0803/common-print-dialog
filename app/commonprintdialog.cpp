#include "commonprintdialog.h"
#include "preview.h"
#include <QGuiApplication>
#include <QQmlContext>
#include <QStringList>
#include <QQuickWidget>
#include <QDebug>
extern "C" {
    #include "../backends/cups/src/print_frontend.h"
}

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
    engine.rootContext()->setContextProperty("preview_data", &data);
}

void _CommonPrintDialog::init_backend() {
    _cpd->f = get_new_FrontendObj(NULL);
    g_thread_new("parse_commands_thread", parse_commands, NULL);
    connect_to_dbus(_cpd->f);
}

gpointer parse_commands(gpointer user_data) {
    for (int i = 0; i < 100000000; i++);
    get_all_printer_options(_cpd->f, "4510DX");
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
