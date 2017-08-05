#ifndef QCPDIALOG_H
#define QCPDIALOG_H

#include "QCPDialog_global.h"

#include <QAbstractPrintDialog>

class QPrinter;
class QGridLayout;
class Tabs;
class Root;
class Preview;
class Controls;

struct _FrontendObj;
using FrontendObj = _FrontendObj;

struct _GMainLoop;
using GMainLoop = _GMainLoop;

struct _PrinterObj;
using PrinterObj = _PrinterObj;

using gpointer = void *;

class CPDSHARED_EXPORT QCPDialog : public QAbstractPrintDialog
{
    Q_OBJECT
public:
    QCPDialog(QPrinter *printer, QWidget *parent = Q_NULLPTR);
    void init_backend();

    void addPrinter(char *printer, char *backend);
    void clearPrinters();

    void addMaximumPrintCopies(char *_copies);

    void updateStartJobsModel(char *startJobOption);
    void clearStartJobsModel();

    void updatePaperSizeModel(char *media, int isDefault);
    void clearPaperSizeModel();

    void addPagesPerSize(char *pages)
    {
        Q_UNUSED(pages);
    }

    QString information();

    int exec() override
    {
        return QDialog::exec();
    }

public Q_SLOTS:
    void tabBarIndexChanged(qint32 index);
    void swipeViewIndexChanged(qint32 index);
    void cancelButtonClicked();
    void newPrinterSelected(const QString &printer);
    void remotePrintersToggled(const QString &enabled);

private:
    FrontendObj *f;
    Tabs *tabs;
    Root *root;
    Preview *preview;
    Controls *controls;
    QGridLayout *masterLayout;
};

#endif // QCPDIALOG_H
