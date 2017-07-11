#ifndef COMMONPRINTDIALOG_H
#define COMMONPRINTDIALOG_H
extern "C" {
    #include <glib.h>
    #include "../backends/cups/src/print_frontend.h"
    #include "../backends/cups/src/CPD.h"
}
#include <QQmlApplicationEngine>


class _CommonPrintDialog
{
public:
    QQmlApplicationEngine engine;
    FrontendObj *f;

    _CommonPrintDialog();
    void init_backend();
    void add(char* printer);
    static gpointer parse_commands(gpointer user_data);
};

class CommonPrintDialog {
public:
    CommonPrintDialog();
    void exec();
};

#endif // COMMONPRINTDIALOG_H
