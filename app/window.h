#ifndef WINDOW_H
#define WINDOW_H

#include <QGridLayout>
#include <QPainter>
#include <QAbstractPrintDialog>
#include <QPrinter>
#include "components.h"

#include <QDebug>

extern "C" {
    #include "../backends/cups/src/CPD.h"
    #include "../backends/cups/src/print_frontend.h"
}

class QPrinter;

static int add_printer_callback(PrinterObj *p);
static int remove_printer_callback(char *printer_name);
void ui_add_printer_aux(gpointer key, gpointer value, gpointer user_data);

typedef struct {
    std::string command;
    std::string arg1;
    std::string arg2;
} Command;

class _Window : public QWidget {
    Q_OBJECT
public:
    FrontendObj *f;
    GMainLoop *loop;
    Tabs *tabs;
    Root *root;
    Preview *preview;
    Controls *controls;
    QGridLayout *masterLayout;

    _Window(QPrinter* printer, QWidget* parent = Q_NULLPTR);
    void init_backend();
    void addPrinter(const char* printer);
    void clearPrinters();
    void addPrinterSupportedMedia(char* media) {}
    void clearPrintersSupportedMedia() {}
    void addMaximumPrintCopies(int copies) {}
    void addJobHoldUntil(char* startJobOption) {}
    void addPagesPerSize(char* pages) {}
    void updateAllOptions(const QString &printer) {}
    gpointer parse_commands(gpointer user_data);
    gpointer ui_add_printer(gpointer user_data);

public Q_SLOTS:
    void tabBarIndexChanged(qint32 index);
    void swipeViewIndexChanged(qint32 index);
    void cancelButtonClicked();
};

class Q_PRINTSUPPORT_EXPORT CPrintDialog : public QAbstractPrintDialog {
public:
    CPrintDialog(QPrinter *printer, QWidget *parent = Q_NULLPTR);
    int exec() override {}
};

#endif // WINDOW_H
