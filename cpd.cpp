#include "cpd.h"
#include "app/window.h"

CPD::CPD(QPrinter *printer, QWidget *parent) :
    QWidget(parent)
{
}

CPD::CPD(QWidget *parent) :
    QWidget(parent)
{
    Window *w = new Window();
    w->show();
}

QString CPD::information() {
    return QString("CPD Library");
}
