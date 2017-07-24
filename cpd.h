#ifndef CPD_H
#define CPD_H

#include "cpd_global.h"
#include <QPrinter>
#include <QWidget>

class Window;

class CPDSHARED_EXPORT CPD : public QWidget
{

public:
    Window *w;
    CPD(QPrinter *printer, QWidget *parent = Q_NULLPTR);
    CPD(QWidget *parent = Q_NULLPTR);
    void show();
    QString information();
};

#endif // CPD_H
