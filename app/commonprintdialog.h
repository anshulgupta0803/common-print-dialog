#ifndef COMMONPRINTDIALOG_H
#define COMMONPRINTDIALOG_H
extern "C" {
    #include <glib.h>
    #include "../backends/cups/src/print_frontend.h"
    #include "../backends/cups/src/CPD.h"
}
#include <QQmlApplicationEngine>
#include <QObject>

//gpointer parse_commands(gpointer user_data);

class _CommonPrintDialog
{
public:
    QQmlApplicationEngine engine;
    FrontendObj *f;
    GMainLoop *loop;

    _CommonPrintDialog();
    void init_backend();
    void addPrinter(const char* printer);
    void clearPrinters();
    void addPrinterSupportedMedia(char* media);
    void clearPrintersSupportedMedia();
    void addMaximumPrintCopies(int copies);
    void addJobHoldUntil(char* startJobOption);
    void addPagesPerSize(char* pages);
    void updateAllOptions(const QString &printer);
};

class CommonPrintDialog {
public:
    CommonPrintDialog();
    void exec();
};

class BackendObject: public QObject {
    Q_OBJECT
public Q_SLOTS:
    void newPrinterSelected(const QString &printer);
    void remotePrintersToggled(const QString enabled);
    void cancelButtonClicked();
};

#endif // COMMONPRINTDIALOG_H
