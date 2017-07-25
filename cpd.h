#ifndef CPD_H
#define CPD_H

#include "cpd_global.h"
#include <QPrinter>
#include <QWidget>

class CPrintDialog;

class CPDSHARED_EXPORT CPD : public QWidget
{

public:
    CPrintDialog *w;
    CPD(QPrinter *printer, QWidget *parent = Q_NULLPTR);
    void showDialog();
    QString information();
};

#endif // CPD_H
