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
#include <QTimer>
#include <QProcess>
#include <QUuid>
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
    controls(new Controls(this)),
    masterLayout(new QGridLayout(this))
{
    uniqueID = QUuid::createUuid().toString().remove('{').remove('}');
    preview = new Preview(printer, uniqueID, this);
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
                     SIGNAL(printButtonClicked()),
                     this,
                     SLOT(printButtonClicked()));


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

    QObject::connect(generalObject,
                     SIGNAL(collateToggled(QString)),
                     this,
                     SLOT(collateToggled(QString)));

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

    setMaximumSize(700, 480);
    setMinimumSize(700, 480);

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

    f = get_new_FrontendObj(uniqueID.toLatin1().data(), add_cb, rem_cb);
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
    p = find_PrinterObj(f, list[0].toLatin1().data(), list[1].toLatin1().data());

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
    QStringList pageSizeSplitList = pageSize.split("_");
    QString size = pageSizeSplitList[2];
    QStringList sizeSplitList = size.split("x");

    qreal width = sizeSplitList[0].toDouble();

    QString unit = sizeSplitList[1].right(2);
    sizeSplitList[1].remove(unit);

    qreal height = sizeSplitList[1].toDouble();

    preview->setPageSize(pageSizeSplitList[1], width, height, unit);
}

void QCPDialog::numCopiesChanged(const int copies)
{
    preview->setNumCopies(copies);
}

void QCPDialog::collateToggled(const QString &enabled)
{
    enabled.compare("true") == 0 ? preview->setCollateCopies(true) : preview->setCollateCopies(false);
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

    reject();   // QDialog::reject()
}

void QCPDialog::printButtonClicked()
{
    //print_file(p, (char *)"/tmp/print.pdf");
    disconnect_from_dbus(f);
//    QProcess *process = new QProcess(this);
//    QString program = "/home/anshul/Desktop/a.out";
//    QStringList args;
//    args << "Arg1" << "Arg2";
//    process->start(program, args);

    accept();   // QDialog::accept()
}

void QCPDialog::checkPdfCreated()
{
    qDebug() << "Child Call";
//    QFile file("/tmp/print.pdf");
//    if (file.exists()) {
//        timer->stop();
//        qDebug() << "Calling print_file";
//        print_file(p, file.fileName().toLatin1().data());
//        //exit(0);
//    }
//    else {
//        timerCount++;
//        qDebug() << timerCount;
//    }
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
