/****************************************************************************
**
**  $QT_BEGIN_LICENSE:GPL$
**
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>
**
**  $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QCPDIALOG_H
#define QCPDIALOG_H

#include "QCPDialog_global.h"
#include "singleton.h"
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

    void resizeEvent(QResizeEvent *event) override;

    void init_backend();

    void clearPrinters();

    void addMaximumPrintCopies(char *_copies);

    void updateStartJobsModel(char *startJobOption);
    void clearStartJobsModel();

    void updatePaperSizeModel(std::string media, int isDefault);
    void clearPaperSizeModel();

    void updatePagesPerSideModel(char *pages, int isDefault);
    void clearPagesPerSideModel();

    QString information();

    int exec() override
    {
        return QDialog::exec();
    }

public Q_SLOTS:
    void addPrinter(char *printer_name, char *printer_id, char *backend_name);
    void removePrinter(char *printer_name);
    void tabBarIndexChanged(qint32 index);
    void swipeViewIndexChanged(qint32 index);
    void cancelButtonClicked();
    void printButtonClicked();
    void checkPdfCreated();
    void newPrinterSelected(const QString &printer);
    void remotePrintersToggled(const QString &enabled);
    void orientationChanged(const QString &orientation);
    void newPageSizeSelected(const QString &pageSize);
    void numCopiesChanged(const int copies);
    void collateToggled(const QString &enabled);
    void newPageRangeSet(const QString &pageRange);

private:
    FrontendObj *f;
    PrinterObj *p;
    Tabs *tabs;
    Root *root;
    Preview *preview;
    Controls *controls;
    QGridLayout *masterLayout;
    QTimer *timer;
    int timerCount = 0;
    QString uniqueID;
};

class CallbackFunctions : public QObject
{
    Q_OBJECT
public:
    explicit CallbackFunctions(QObject *parent = 0);
    static void add_printer_callback(PrinterObj *p);
    static void remove_printer_callback(PrinterObj *p);

Q_SIGNALS:
    void addPrinterSignal(char *printer_name, char *printer_id, char *backend_name);
    void removePrinterSignal(char *printer_name);

};

typedef Singleton<CallbackFunctions> cbf;

#endif // QCPDIALOG_H
