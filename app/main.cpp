#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "preview.h"
#include <QQmlContext>

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.addImageProvider(QLatin1String("preview"), new QPdfPreview);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    QPreviewData data;
    engine.rootContext()->setContextProperty("preview_data", &data);

    return app.exec();
}
