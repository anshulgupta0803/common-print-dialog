#include "cpd.h"
#include "app/window.h"

CPD::CPD(QPrinter *printer, QWidget *parent) :
    QWidget(parent)
{
    w = new CPrintDialog(printer, parent);
}

void CPD::showDialog() {
    w->show();
}

QString CPD::information() {
    return QString("CPD Library");
}
