#include "cpd.h"
#include "app/window.h"

CPD::CPD(QPrinter *printer, QWidget *parent) :
    QWidget(parent)
{
}

CPD::CPD(QWidget *parent) :
    QWidget(parent)
{
    w = new Window();
}

void CPD::show() {
    w->show();
}

QString CPD::information() {
    return QString("CPD Library");
}
