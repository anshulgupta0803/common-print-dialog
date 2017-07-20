#ifndef CPD_H
#define CPD_H

#include "cpd_global.h"
#include <QPrinter>
#include <QWidget>

class CPDSHARED_EXPORT CommonPrintDialogLibrary : public QWidget
{

public:
    CommonPrintDialogLibrary(QPrinter *printer, QWidget *parent = Q_NULLPTR);
    CommonPrintDialogLibrary(QWidget *parent = Q_NULLPTR);
    QString information();
};

#endif // CPD_H
