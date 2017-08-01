#include "cpd.h"
#include "app/QCPDialog.h"

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
