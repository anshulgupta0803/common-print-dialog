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

CommonPrintDialog::CommonPrintDialog() {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    engine.addImageProvider(QLatin1String("preview"), new QPdfPreview);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    QPreviewData data;
    engine.rootContext()->setContextProperty("preview_data", &data);

    QStringList dataList;
    dataList.append("Item 1");
    dataList.append("Item 2");
    dataList.append("Item 3");
    dataList.append("Item 4");
    engine.rootContext()->setContextProperty("destinationModel", QVariant::fromValue(dataList));
}

void CommonPrintDialog::exec() {
    QQuickWidget(&engine, Q_NULLPTR);
    main_frontend();
}
