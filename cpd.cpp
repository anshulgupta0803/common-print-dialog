#include "cpd.h"
#include "app/window.h"

CommonPrintDialogLibrary::CommonPrintDialogLibrary(QPrinter *printer, QWidget *parent) :
    QWidget(parent)
{
}

CommonPrintDialogLibrary::CommonPrintDialogLibrary(QWidget *parent) :
    QWidget(parent)
{
    Window *w = new Window();
    w->show();
}

QString CommonPrintDialogLibrary::information() {
    return QString("CPD Library");
}
