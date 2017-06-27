#ifndef COMMONPRINTDIALOG_H
#define COMMONPRINTDIALOG_H

#include <QQmlApplicationEngine>

class _CommonPrintDialog
{
public:
    QQmlApplicationEngine engine;
    _CommonPrintDialog();
    void add(char* printer);
};

class CommonPrintDialog {
public:
    CommonPrintDialog();
    void exec();
};

#endif // COMMONPRINTDIALOG_H
