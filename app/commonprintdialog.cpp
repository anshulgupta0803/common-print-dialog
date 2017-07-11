#include "commonprintdialog.h"
#include "preview.h"
#include <QGuiApplication>
#include <QQmlContext>
#include <QStringList>
#include <QQuickWidget>
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
    //g_thread_new("parse_commands_thread", parse_commands, NULL);
    connect_to_dbus(_cpd->f);
}

gpointer _CommonPrintDialog::parse_commands(gpointer user_data) {
    for (int i = 0; i < 100000000; i++);
    get_all_printer_options(_cpd->f, "X950");
}

void _CommonPrintDialog::add(char *printer) {
    QVariant returnedValue;
    QVariant arg = printer;
    QMetaObject::invokeMethod((_cpd->engine).rootObjects().at(0),
                              "updateDestinationModel",
                              Q_RETURN_ARG(QVariant, returnedValue),
                              Q_ARG(QVariant, arg));
}

void ui_add_printer(char* printer) {
    _cpd->add(printer);
}
