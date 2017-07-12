#ifndef COMMONPRINTDIALOG_H
#define COMMONPRINTDIALOG_H
extern "C" {
    #include <glib.h>
    #include "../backends/cups/src/print_frontend.h"
    #include "../backends/cups/src/CPD.h"
}
#include <QQmlApplicationEngine>

gpointer parse_commands(gpointer user_data);

class _CommonPrintDialog
{
public:
    QQmlApplicationEngine engine;
    FrontendObj *f;

    _CommonPrintDialog();
    void init_backend();
    void addPrinter(char* printer);
    void addPrinterSupportedMedia(char* media);
};

class CommonPrintDialog {
public:
    CommonPrintDialog();
    void exec();
};

#endif // COMMONPRINTDIALOG_H
