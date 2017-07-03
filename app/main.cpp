#include <QtGui>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QObject>
#include <QtQuickWidgets>
#include "commonprintdialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
//    QWidget window;
//    window.resize(300, 300);
//    window.setWindowTitle("Application");
//    window.show();

//    QLabel *label = new QLabel("Hello World", &window);
//    label->move((window.width() / 2) - (label->width() / 2),
//                 (window.height() / 2) - (label->height() / 2));
//    label->show();

    CommonPrintDialog cpd;
    cpd.exec();

    return app.exec();
}
