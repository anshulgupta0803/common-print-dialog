#ifndef COMMONPRINTDIALOG_H
#define COMMONPRINTDIALOG_H

#include <QWidget>
#include <QQmlApplicationEngine>
#include <QWidget>
class CommonPrintDialog : public QWidget
{
public:
    QQmlApplicationEngine engine;
    CommonPrintDialog();
    void exec();
};

#endif // COMMONPRINTDIALOG_H
