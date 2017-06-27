#include "commonprintdialog.h"
#include "preview.h"
#include <QGuiApplication>
#include <QQmlContext>
#include <QStringList>
#include <QQuickWidget>
extern "C" {
    #include "../backends/cups/print_backend_cups.h"
    #include "../backends/cups/print_frontend.h"
}

_CommonPrintDialog *_cpd;

CommonPrintDialog::CommonPrintDialog() {
    _cpd = new _CommonPrintDialog;
}

void CommonPrintDialog::exec() {
    QQuickWidget(&(_cpd->engine), Q_NULLPTR);
    main_frontend();
}

_CommonPrintDialog::_CommonPrintDialog() {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    engine.addImageProvider(QLatin1String("preview"), new QPdfPreview);
    engine.load(QUrl(QLatin1String("qrc:/app/main.qml")));
    QPreviewData data;
    engine.rootContext()->setContextProperty("preview_data", &data);
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
