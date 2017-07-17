#include "commonprintdialog.h"
#include "window.h"
#include <QtGui>
#include <QApplication>
#include <QWidget>
#include <QLabel>

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

    //CommonPrintDialog cpd;
    //cpd.exec();

    Window *w = new Window();
    w->show();

    return app.exec();
}
