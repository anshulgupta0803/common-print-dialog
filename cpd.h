#ifndef CPD_H
#define CPD_H

#include "cpd_global.h"
#include <QPrinter>
#include <QWidget>

class CPDSHARED_EXPORT CPD : public QWidget
{

public:
    CPD(QPrinter *printer, QWidget *parent = Q_NULLPTR);
    CPD(QWidget *parent = Q_NULLPTR);
    QString information();
};

#endif // CPD_H
