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

#include "QCPDialog.h"
#include <QGridLayout>
#include <QQuickItem>
#include "components.h"
#include <cstring>

extern "C" {
#include <CPDFrontend.h>
}

/*!
 *  \class QCPDialog
 *  \inmodule Common Print Dialog
 *
 *  This class acts as the main window for the common print dialog. It is a container to
 *  widget objects namely tabs, root, preview and controls.
 *
 *  masterLayout
 *      |-tabs
 *      |-root -- preview
 *      |-controls
 *
 */

/*!
 * \fn QCPDialog::QCPDialog(QPrinter *printer, QWidget *parent)
 *
 *  Constructs QCPDialog with \a parent as the parent widget and \a printer as the printer. The
 *  \a printer handles all the job options that get reflected in the preview as well as the final
 *  job output.
 */
QCPDialog::QCPDialog(QPrinter *printer, QWidget *parent) :
    QAbstractPrintDialog (printer, parent),
    tabs(new Tabs(this)),
    root(new Root(this)),
    preview(new Preview(printer, this)),
    controls(new Controls(this)),
    masterLayout(new QGridLayout(this))
{
    QObject::connect(tabs->rootObject,
                     SIGNAL(tabBarIndexChanged(qint32)),
                     this,
                     SLOT(tabBarIndexChanged(qint32)));

    QObject::connect(root->rootObject,
                     SIGNAL(swipeViewIndexChanged(qint32)),
                     this,
                     SLOT(swipeViewIndexChanged(qint32)));

    QObject::connect(controls->rootObject,
                     SIGNAL(cancelButtonClicked()),
                     this,
                     SLOT(cancelButtonClicked()));

    QObject::connect(controls->rootObject,
                     SIGNAL(zoomSliderValueChanged(qreal)),
                     preview,
                     SLOT(setZoom(qreal)));

    QObject::connect(controls->rootObject,
                     SIGNAL(nextPageButtonClicked()),
                     preview,
                     SLOT(showNextPage()));

    QObject::connect(controls->rootObject,
                     SIGNAL(prevPageButtonClicked()),
                     preview,
                     SLOT(showPrevPage()));

    QObject *generalObject = root->rootObject->findChild<QObject *>("generalObject");

    QObject::connect(generalObject,
                     SIGNAL(newPrinterSelected(QString)),
                     this,
                     SLOT(newPrinterSelected(QString)));

    QObject::connect(generalObject,
                     SIGNAL(remotePrintersToggled(QString)),
                     this,
                     SLOT(remotePrintersToggled(QString)));

    QObject::connect(generalObject,
                     SIGNAL(orientationChanged(QString)),
                     this,
                     SLOT(orientationChanged(QString)));

    QObject::connect(generalObject,
                     SIGNAL(newPageSizeSelected(QString)),
                     this,
                     SLOT(newPageSizeSelected(QString)));

    QObject::connect(cbf::Instance(),
                     SIGNAL(addPrinterSignal(char *, char *, char *)),
                     this,
                     SLOT(addPrinter(char *, char *, char *)));

    QObject::connect(cbf::Instance(),
                     SIGNAL(removePrinterSignal(char *)),
                     this,
                     SLOT(removePrinter(char *)));

    tabs->setMinimumSize(700, 32);

    root->setMinimumSize(320, 408);

    preview->setMinimumSize(380, 408);

    controls->setMinimumSize(700, 40);

    masterLayout->setColumnMinimumWidth(0, 320);
    masterLayout->setColumnMinimumWidth(1, 380);
    masterLayout->setRowMinimumHeight(0, 32);
    masterLayout->setRowMinimumHeight(1, 408);
    masterLayout->setRowMinimumHeight(2, 40);
    masterLayout->setSpacing(0);
    masterLayout->setMargin(0);

    masterLayout->addWidget(tabs,     0, 0, 1, 2);
    masterLayout->addWidget(root,     1, 0, 1, 1);
    masterLayout->addWidget(preview,  1, 1, 1, 1);
    masterLayout->addWidget(controls, 2, 0, 1, 2);

    adjustSize();

    //setMaximumSize(700, 480);
    //setMinimumSize(700, 480);

    init_backend();
}

void QCPDialog::resizeEvent(QResizeEvent *event)
{
    event->accept();
    tabs->resize(masterLayout->itemAt(0)->geometry());
    root->resize(masterLayout->itemAt(1)->geometry());
    preview->resize(masterLayout->itemAt(2)->geometry());
    controls->resize(masterLayout->itemAt(3)->geometry());
}

/*!
 * \fn void QCPDialog::init_backend()
 *
 *  This function is called whenever a new instance of the dialog is created. This function helps
 *  create a new FrontendObj for a new instance of the dialog and connects the FrontendObj to the
 *  dbus for further communication.
 */
void QCPDialog::init_backend()
{
    event_callback add_cb = (event_callback)CallbackFunctions::add_printer_callback;
    event_callback rem_cb = (event_callback)CallbackFunctions::remove_printer_callback;
    f = get_new_FrontendObj(NULL, add_cb, rem_cb);
    connect_to_dbus(f);
}

/*!
 *  \fn static void CallbackFunctions::CallbackFunctions(QObject *parent)
 *
 *  A singleton class which acts as a mediator between a static callback
 *  function and QCPDialog class
 */
CallbackFunctions::CallbackFunctions(QObject *parent):
    QObject (parent)
{
}

/*!
 *  \fn static void CallbackFunctions::add_printer_callback(PrinterObj *p)
 *
 *  Acts as a callback function whenever a new PrinterObj \a p is added.
 */
void CallbackFunctions::add_printer_callback(PrinterObj *p)
{
    cbf::Instance()->addPrinterSignal(p->name, p->id, p->backend_name);
}

/*!
 *  \fn static void CallbackFunctions::remove_printer_callback(PrinterObj *p)
 *
 *  Acts as a callback function whenever a PrinterObj \a p is removed.
 */
void CallbackFunctions::remove_printer_callback(PrinterObj *p)
{
    cbf::Instance()->removePrinterSignal(p->name);
}

/*!
 *  \fn void QCPDialog::addPrinter(char *printer_name, char *printer_id, char *backend_name)
 *
 *  Whenever a new printer with name \a printer_name, id \a printer_id and backend \a backend_name
 *  is discovered in the backends, this function is called which adds that printer to the UI.
 */
void QCPDialog::addPrinter(char *printer_name, char *printer_id, char *backend_name)
{
    QObject *obj = root->rootObject->findChild<QObject *>("generalObject");
    if (obj)
        QMetaObject::invokeMethod(obj,
                                  "addToDestinationModel",
                                  Q_ARG(QVariant, printer_name),
                                  Q_ARG(QVariant, printer_id),
                                  Q_ARG(QVariant, backend_name));
    else
        qDebug() << "generalObject Not Found";
}

/*!
 *  \fn void QCPDialog::removePrinter(char *printer_name)
 *
 *  Whenever a printer with name \a printer_name is removed,
 *  this function is called which removes that printer to the UI.
 */
void QCPDialog::removePrinter(char *printer_name)
{
    QObject *obj = root->rootObject->findChild<QObject *>("generalObject");
    if (obj)
        QMetaObject::invokeMethod(obj,
                                  "removeFromDestinationModel",
                                  Q_ARG(QVariant, printer_name));
    else
        qDebug() << "generalObject Not Found";
}

/*!
 *  \fn void QCPDialog::clearPrinters()
 *
 *  This function clears the list of printers shown in the UI.
 */
void QCPDialog::clearPrinters()
{
    QObject *obj = root->rootObject->findChild<QObject *>("generalObject");
    if (obj)
        QMetaObject::invokeMethod(obj, "clearDestinationModel");
    else
        qDebug() << "generalObject Not Found";
}

/*!
 *  \fn void QCPDialog::newPrinterSelected(const QString &printer)
 *
 *  Whenever a new printer with name \a printer is selected by the User, this function updates all
 *  the options shown in the dialog with the options and values supported by the selected printer.
 */
void QCPDialog::newPrinterSelected(const QString &printer)
{
    QStringList list = printer.split('#');  // printer is in the format: <printer_id>#<backend_name>
    PrinterObj *p = find_PrinterObj(f, list[0].toLatin1().data(), list[1].toLatin1().data());

    Options *options = get_all_options(p);

    GHashTableIter iter;
    g_hash_table_iter_init(&iter, options->table);
    gpointer _key, _value;

    while (g_hash_table_iter_next(&iter, &_key, &_value)) {
        char *key = static_cast<char *>(_key);
        Option *value = static_cast<Option *>(_value);
        if (strncmp(key, "copies", 6) == 0) {
            for (int i = 0; i < value->num_supported; i++)
                addMaximumPrintCopies(value->supported_values[i]);
        } else if (strncmp(key, "finishings", 10) == 0) {

        } else if (strncmp(key, "ipp-attribute-fidelity", 22) == 0) {

        } else if (strncmp(key, "job-hold-until", 14) == 0) {
            clearStartJobsModel();
            for (int i = 0; i < value->num_supported; i++)
                updateStartJobsModel(value->supported_values[i]);
        } else if (strncmp(key, "job-name", 8) == 0) {

        } else if (strncmp(key, "job-priority", 12) == 0) {

        } else if (strncmp(key, "job-sheets", 10) == 0) {

        } else if (strncmp(key, "media-col", 9) == 0) {

        } else if (strncmp(key, "media", 5) == 0) {
            clearPaperSizeModel();
            for (int i = 0; i < value->num_supported; i++)
                updatePaperSizeModel(std::string(value->supported_values[i]),
                                     strcmp(value->supported_values[i], value->default_value));
        } else if (strncmp(key, "multiple-document-handling", 26) == 0) {

        } else if (strncmp(key, "number-up", 9) == 0) {
            clearPagesPerSideModel();
            for (int i = 0; i < value->num_supported; i++)
                updatePagesPerSideModel(value->supported_values[i],
                                        strcmp(value->supported_values[i], value->default_value));

        } else if (strncmp(key, "output-bin", 10) == 0) {

        } else if (strncmp(key, "orientation-requested", 21) == 0) {

        } else if (strncmp(key, "page-ranges", 11) == 0) {

        } else if (strncmp(key, "print-color-mode", 16) == 0) {

        } else if (strncmp(key, "print-quality", 13) == 0) {

        } else if (strncmp(key, "printer-resolution", 18) == 0) {

        } else if (strncmp(key, "sides", 5) == 0) {

        } else {
            qDebug() << "Unhandled Option:" << key;
        }
    }
}

/*!
 *  \fn void QCPDialog::remotePrintersToggled(const QString &enabled)
 *
 *  When \a enabled is set to "true", the dialog shows all printers including remote printers
 *  whereas when it is not set to "true", the dialog hides all the remote printers and shows
 *  only the local printers.
 */
void QCPDialog::remotePrintersToggled(const QString &enabled)
{
    enabled.compare("true") == 0 ? unhide_remote_cups_printers(f) : hide_remote_cups_printers(f);
}

void QCPDialog::orientationChanged(const QString &orientation)
{
    preview->setOrientation(orientation);
}

void QCPDialog::newPageSizeSelected(const QString &pageSize)
{
    QSizeF size;
    if (pageSize.compare("TabloidExtra", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::TabloidExtra, QPageSize::Unit::Point);
    } else if (pageSize.compare("Tabloid", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::Tabloid, QPageSize::Unit::Point);
    } else if (pageSize.compare("SuperB", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::SuperB, QPageSize::Unit::Point);
    } else if (pageSize.compare("SuperA", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::SuperA, QPageSize::Unit::Point);
    } else if (pageSize.compare("Statement", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::Statement, QPageSize::Unit::Point);
    } else if (pageSize.compare("Quarto", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::Quarto, QPageSize::Unit::Point);
    } else if (pageSize.compare("Prc32KBig", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::Prc32KBig, QPageSize::Unit::Point);
    } else if (pageSize.compare("Prc32K", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::Prc32K, QPageSize::Unit::Point);
    } else if (pageSize.compare("Prc16K", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::Prc16K, QPageSize::Unit::Point);
    } else if (pageSize.compare("Postcard", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::Postcard, QPageSize::Unit::Point);
    } else if (pageSize.compare("Note", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::Note, QPageSize::Unit::Point);
    } else if (pageSize.compare("LetterSmall", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::LetterSmall, QPageSize::Unit::Point);
    } else if (pageSize.compare("LetterPlus", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::LetterPlus, QPageSize::Unit::Point);
    } else if (pageSize.compare("LetterExtra", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::LetterExtra, QPageSize::Unit::Point);
    } else if (pageSize.compare("Letter", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::Letter, QPageSize::Unit::Point);
    } else if (pageSize.compare("LegalExtra", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::LegalExtra, QPageSize::Unit::Point);
    } else if (pageSize.compare("Legal", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::Legal, QPageSize::Unit::Point);
    } else if (pageSize.compare("Ledger", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::Ledger, QPageSize::Unit::Point);
    } else if (pageSize.compare("JisB9", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::JisB9, QPageSize::Unit::Point);
    } else if (pageSize.compare("JisB8", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::JisB8, QPageSize::Unit::Point);
    } else if (pageSize.compare("JisB7", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::JisB7, QPageSize::Unit::Point);
    } else if (pageSize.compare("JisB6", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::JisB6, QPageSize::Unit::Point);
    } else if (pageSize.compare("JisB5", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::JisB5, QPageSize::Unit::Point);
    } else if (pageSize.compare("JisB4", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::JisB4, QPageSize::Unit::Point);
    } else if (pageSize.compare("JisB3", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::JisB3, QPageSize::Unit::Point);
    } else if (pageSize.compare("JisB2", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::JisB2, QPageSize::Unit::Point);
    } else if (pageSize.compare("JisB10", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::JisB10, QPageSize::Unit::Point);
    } else if (pageSize.compare("JisB1", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::JisB1, QPageSize::Unit::Point);
    } else if (pageSize.compare("JisB0", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::JisB0, QPageSize::Unit::Point);
    } else if (pageSize.compare("Imperial9x12", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::Imperial9x12, QPageSize::Unit::Point);
    } else if (pageSize.compare("Imperial9x11", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::Imperial9x11, QPageSize::Unit::Point);
    } else if (pageSize.compare("Imperial8x10", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::Imperial8x10, QPageSize::Unit::Point);
    } else if (pageSize.compare("Imperial7x9", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::Imperial7x9, QPageSize::Unit::Point);
    } else if (pageSize.compare("Imperial15x11", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::Imperial15x11, QPageSize::Unit::Point);
    } else if (pageSize.compare("Imperial12x11", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::Imperial12x11, QPageSize::Unit::Point);
    } else if (pageSize.compare("Imperial10x14", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::Imperial10x14, QPageSize::Unit::Point);
    } else if (pageSize.compare("Imperial10x13", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::Imperial10x13, QPageSize::Unit::Point);
    } else if (pageSize.compare("Imperial10x11", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::Imperial10x11, QPageSize::Unit::Point);
    } else if (pageSize.compare("Folio", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::Folio, QPageSize::Unit::Point);
    } else if (pageSize.compare("FanFoldUS", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::FanFoldUS, QPageSize::Unit::Point);
    } else if (pageSize.compare("FanFoldGermanLegal", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::FanFoldGermanLegal, QPageSize::Unit::Point);
    } else if (pageSize.compare("FanFoldGerman", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::FanFoldGerman, QPageSize::Unit::Point);
    } else if (pageSize.compare("ExecutiveStandard", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::ExecutiveStandard, QPageSize::Unit::Point);
    } else if (pageSize.compare("Executive", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::Executive, QPageSize::Unit::Point);
    } else if (pageSize.compare("EnvYou4", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::EnvelopeYou4, QPageSize::Unit::Point);
    } else if (pageSize.compare("EnvPrc9", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::EnvelopePrc9, QPageSize::Unit::Point);
    } else if (pageSize.compare("EnvPrc8", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::EnvelopePrc8, QPageSize::Unit::Point);
    } else if (pageSize.compare("EnvPrc7", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::EnvelopePrc7, QPageSize::Unit::Point);
    } else if (pageSize.compare("EnvPrc6", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::EnvelopePrc6, QPageSize::Unit::Point);
    } else if (pageSize.compare("EnvPrc5", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::EnvelopePrc5, QPageSize::Unit::Point);
    } else if (pageSize.compare("EnvPrc4", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::EnvelopePrc4, QPageSize::Unit::Point);
    } else if (pageSize.compare("EnvPrc3", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::EnvelopePrc3, QPageSize::Unit::Point);
    } else if (pageSize.compare("EnvPrc2", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::EnvelopePrc2, QPageSize::Unit::Point);
    } else if (pageSize.compare("EnvPrc10", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::EnvelopePrc10, QPageSize::Unit::Point);
    } else if (pageSize.compare("EnvPrc1", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::EnvelopePrc1, QPageSize::Unit::Point);
    } else if (pageSize.compare("EnvPersonal", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::EnvelopePersonal, QPageSize::Unit::Point);
    } else if (pageSize.compare("EnvMonarch", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::EnvelopeMonarch, QPageSize::Unit::Point);
    } else if (pageSize.compare("EnvKaku3", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::EnvelopeKaku3, QPageSize::Unit::Point);
    } else if (pageSize.compare("EnvKaku2", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::EnvelopeKaku2, QPageSize::Unit::Point);
    } else if (pageSize.compare("EnvItalian", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::EnvelopeItalian, QPageSize::Unit::Point);
    } else if (pageSize.compare("EnvInvite", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::EnvelopeInvite, QPageSize::Unit::Point);
    } else if (pageSize.compare("EnvDL", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::EnvelopeDL, QPageSize::Unit::Point);
    } else if (pageSize.compare("EnvChou4", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::EnvelopeChou4, QPageSize::Unit::Point);
    } else if (pageSize.compare("EnvChou3", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::EnvelopeChou3, QPageSize::Unit::Point);
    } else if (pageSize.compare("EnvC7", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::EnvelopeC7, QPageSize::Unit::Point);
    } else if (pageSize.compare("EnvC65", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::EnvelopeC65, QPageSize::Unit::Point);
    } else if (pageSize.compare("EnvC6", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::EnvelopeC6, QPageSize::Unit::Point);
    } else if (pageSize.compare("EnvC5", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::EnvelopeC5, QPageSize::Unit::Point);
    } else if (pageSize.compare("EnvC4", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::EnvelopeC4, QPageSize::Unit::Point);
    } else if (pageSize.compare("EnvC3", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::EnvelopeC3, QPageSize::Unit::Point);
    } else if (pageSize.compare("EnvC2", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::EnvelopeC2, QPageSize::Unit::Point);
    } else if (pageSize.compare("EnvC1", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::EnvelopeC1, QPageSize::Unit::Point);
    } else if (pageSize.compare("EnvC0", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::EnvelopeC0, QPageSize::Unit::Point);
    } else if (pageSize.compare("EnvB6", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::EnvelopeB6, QPageSize::Unit::Point);
    } else if (pageSize.compare("EnvB5", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::EnvelopeB5, QPageSize::Unit::Point);
    } else if (pageSize.compare("EnvB4", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::EnvelopeB4, QPageSize::Unit::Point);
    } else if (pageSize.compare("Env9", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::Envelope9, QPageSize::Unit::Point);
    } else if (pageSize.compare("Env14", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::Envelope14, QPageSize::Unit::Point);
    } else if (pageSize.compare("Env12", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::Envelope12, QPageSize::Unit::Point);
    } else if (pageSize.compare("Env11", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::Envelope11, QPageSize::Unit::Point);
    } else if (pageSize.compare("Env10", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::Envelope10, QPageSize::Unit::Point);
    } else if (pageSize.compare("DoublePostcard", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::DoublePostcard, QPageSize::Unit::Point);
    } else if (pageSize.compare("DLE", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::DLE, QPageSize::Unit::Point);
    } else if (pageSize.compare("Comm10E", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::Comm10E, QPageSize::Unit::Point);
    } else if (pageSize.compare("C5E", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::C5E, QPageSize::Unit::Point);
    } else if (pageSize.compare("B9", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::B9, QPageSize::Unit::Point);
    } else if (pageSize.compare("B8", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::B8, QPageSize::Unit::Point);
    } else if (pageSize.compare("B7", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::B7, QPageSize::Unit::Point);
    } else if (pageSize.compare("B6", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::B6, QPageSize::Unit::Point);
    } else if (pageSize.compare("B5Extra", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::B5Extra, QPageSize::Unit::Point);
    } else if (pageSize.compare("B5", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::B5, QPageSize::Unit::Point);
    } else if (pageSize.compare("B4", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::B4, QPageSize::Unit::Point);
    } else if (pageSize.compare("B3", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::B3, QPageSize::Unit::Point);
    } else if (pageSize.compare("B2", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::B2, QPageSize::Unit::Point);
    } else if (pageSize.compare("B10", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::B10, QPageSize::Unit::Point);
    } else if (pageSize.compare("B1", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::B1, QPageSize::Unit::Point);
    } else if (pageSize.compare("B0", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::B0, QPageSize::Unit::Point);
    } else if (pageSize.compare("ArchE", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::ArchE, QPageSize::Unit::Point);
    } else if (pageSize.compare("ArchD", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::ArchD, QPageSize::Unit::Point);
    } else if (pageSize.compare("ArchC", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::ArchC, QPageSize::Unit::Point);
    } else if (pageSize.compare("ArchB", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::ArchB, QPageSize::Unit::Point);
    } else if (pageSize.compare("ArchA", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::ArchA, QPageSize::Unit::Point);
    } else if (pageSize.compare("AnsiE", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::AnsiE, QPageSize::Unit::Point);
    } else if (pageSize.compare("AnsiD", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::AnsiD, QPageSize::Unit::Point);
    } else if (pageSize.compare("AnsiC", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::AnsiC, QPageSize::Unit::Point);
    } else if (pageSize.compare("AnsiB", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::AnsiB, QPageSize::Unit::Point);
    } else if (pageSize.compare("AnsiA", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::AnsiA, QPageSize::Unit::Point);
    } else if (pageSize.compare("A9", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::A9, QPageSize::Unit::Point);
    } else if (pageSize.compare("A8", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::A8, QPageSize::Unit::Point);
    } else if (pageSize.compare("A7", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::A7, QPageSize::Unit::Point);
    } else if (pageSize.compare("A6", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::A6, QPageSize::Unit::Point);
    } else if (pageSize.compare("A5Extra", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::A5Extra, QPageSize::Unit::Point);
    } else if (pageSize.compare("A5", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::A5, QPageSize::Unit::Point);
    } else if (pageSize.compare("A4Small", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::A4Small, QPageSize::Unit::Point);
    } else if (pageSize.compare("A4Plus", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::A4Plus, QPageSize::Unit::Point);
    } else if (pageSize.compare("A4Extra", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::A4Extra, QPageSize::Unit::Point);
    } else if (pageSize.compare("A4", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::A4, QPageSize::Unit::Point);
    } else if (pageSize.compare("A3Extra", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::A3Extra, QPageSize::Unit::Point);
    } else if (pageSize.compare("A3", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::A3, QPageSize::Unit::Point);
    } else if (pageSize.compare("A2", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::A2, QPageSize::Unit::Point);
    } else if (pageSize.compare("A10", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::A10, QPageSize::Unit::Point);
    } else if (pageSize.compare("A1", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::A1, QPageSize::Unit::Point);
    } else if (pageSize.compare("A0", Qt::CaseInsensitive) == 0) {
        size = QPageSize::size(QPageSize::PageSizeId::A0, QPageSize::Unit::Point);
    } else if (pageSize.contains("Custom", Qt::CaseInsensitive)) {
        size = QSizeF(1, 1);
        qDebug() << "Handle custom page size";
    } else {
        size = QSizeF(1, 1);
        qDebug() << "Unhandled Page Size:" << pageSize;
    }

    preview->setPageSize(size);
}

/*!
 *  \fn void QCPDialog::addMaximumPrintCopies(char *_copies)
 *
 *  This function takes the range \a _copies for the number of copies and sets the maximum value
 *  allowed in the dialog.
 */
void QCPDialog::addMaximumPrintCopies(char *_copies)
{
    QString copies(_copies);
    QStringList list = copies.split('-'); // copies is in this format: 1-9999

    QObject *obj = root->rootObject->findChild<QObject *>("generalObject");
    if (obj)
        obj->setProperty("maximumCopies", list[1].toInt());
    else
        qDebug() << "generalObject Not Found";
}

/*!
 *  \fn void QCPDialog::updateStartJobsModel(char *startJobOption)
 *
 *  Many printers come with a hold option which specifies when the job should start after a user
 *  clicked the "Print" button in the UI. This function adds a new \a startJobOption to the
 *  existing model.
 */
void QCPDialog::updateStartJobsModel(char *startJobOption)
{
    QObject *obj = root->rootObject->findChild<QObject *>("jobsObject");
    if (obj)
        QMetaObject::invokeMethod(obj, "updateStartJobsModel", Q_ARG(QVariant, startJobOption));
    else
        qDebug() << "jobsObject Not Found";
}

/*!
 *  \fn void QCPDialog::clearStartJobsModel()
 *
 *  This function clears the model startJobModel which holds a list of printer-supported job hold
 *  options.
 */
void QCPDialog::clearStartJobsModel()
{
    QObject *obj = root->rootObject->findChild<QObject *>("jobsObject");
    if (obj)
        QMetaObject::invokeMethod(obj, "clearStartJobsModel");
    else
        qDebug() << "jobsObject Not Found";
}

/*!
 *  \fn void QCPDialog::updatePaperSizeModel(char *media, int isDefault)
 *
 *  Adds a new paper defined by \a media to the existing model paperSizeModel. The \a isDefault
 *  parameter checks if the given media is to be set as the default for the printer.
 */
void QCPDialog::updatePaperSizeModel(std::string media, int isDefault)
{
    std::size_t found = media.find(" (Borderless)");
    if (found != std::string::npos)
        media = media.substr(0, found);
    QObject *obj = root->rootObject->findChild<QObject *>("generalObject");
    if (obj)
        QMetaObject::invokeMethod(obj,
                                  "updatePaperSizeModel",
                                  Q_ARG(QVariant, media.c_str()),
                                  Q_ARG(QVariant, isDefault));
    else
        qDebug() << "generalObject Not Found";
}

/*!
 *  \fn void QCPDialog::clearPaperSizeModel()
 *
 *  This function clears the model paperSizeModel which holds a list of printer-supported media
 *  options.
 */
void QCPDialog::clearPaperSizeModel()
{
    QObject *obj = root->rootObject->findChild<QObject *>("generalObject");
    if (obj)
        QMetaObject::invokeMethod(obj, "clearPaperSizeModel");
    else
        qDebug() << "generalObject Not Found";
}

void QCPDialog::updatePagesPerSideModel(char *pages, int isDefault)
{
    QObject *obj = root->rootObject->findChild<QObject *>("pageSetupObject");
    if (obj)
        QMetaObject::invokeMethod(obj,
                                  "updatePagesPerSideModel",
                                  Q_ARG(QVariant, pages),
                                  Q_ARG(QVariant, isDefault));
    else
        qDebug() << "pageSetupObject Not Found";
}

void QCPDialog::clearPagesPerSideModel()
{
    QObject *obj = root->rootObject->findChild<QObject *>("pageSetupObject");
    if (obj)
        QMetaObject::invokeMethod(obj, "clearPagesPerSideModel");
    else
        qDebug() << "pageSetupObject Not Found";
}

/*!
 * \fn void QCPDialog::tabBarIndexChanged(qint32 index)
 *
 *  This function acts as slot for the signal tabBarIndexChanged which is emitted from Tabs.qml
 *  It sets the property "index" in Tabs.qml to \a index
 */
void QCPDialog::tabBarIndexChanged(qint32 index)
{
    root->rootObject->setProperty("index", index);
}

/*!
 * \fn void QCPDialog::swipeViewIndexChanged(qint32 index)
 *
 *  This function acts as slot for the signal swipeViewIndexChanged which is emitted from Root.qml
 *  It sets the property "index" in Root.qml to \a index
 */
void QCPDialog::swipeViewIndexChanged(qint32 index)
{
    tabs->rootObject->setProperty("index", index);
}

/*!
 * \fn void QCPDialog::cancelButtonClicked()
 *
 *  This function acts as a slot for the signal cancelButtonClicked emitted from the
 *  Controls.qml file. The signal is emitted when the user clicks on the "Cancel" Button
 *  in the sidebar.
 */
void QCPDialog::cancelButtonClicked()
{
    disconnect_from_dbus(f);
    close();
}

/*!
 *  \fn QString QCPDialog::information()
 *
 *  Returns the information regarding the dialog.
 */
QString QCPDialog::information()
{
    return "CPD Library";
}
