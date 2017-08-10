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

    static void add_printer_callback(PrinterObj *p);
    static void remove_printer_callback(PrinterObj *p);

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
