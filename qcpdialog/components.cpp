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

#include "components.h"
#include <QSize>

/*! \class Tabs
 *  \inmodule Common Print Dialog
 *
 *  Tabs class handles all the buttons in the topbar
 */

/*!
 * \fn Tabs::Tabs(QWidget *parent)
 *
 *  Constructs Tabs objects with \a parent.
 */
Tabs::Tabs(QWidget *parent) :
    QWidget(parent),
    tabs(new QQuickWidget(QUrl("qrc:/Tabs.qml"), this))
{

    tabs->setResizeMode(QQuickWidget::SizeRootObjectToView);
    tabs->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    rootObject = tabs->rootObject();
}

void Tabs::resize(const QRect &rect)
{
    QWidget::resize(rect.width(), rect.height());
    tabs->resize(rect.width(), rect.height());
}

/*! \class Root
 *  \inmodule Common Print Dialog
 *
 *  Root class creates a QQuickWidget from Root.qml
 */

/*!
 * \fn Root::Root(QWidget *parent)
 *
 *  Constructs Root objects with \a parent.
 */
Root::Root(QWidget *parent) :
    QWidget(parent),
    root(new QQuickWidget(QUrl("qrc:/Root.qml"), this))
{

    root->setResizeMode(QQuickWidget::SizeRootObjectToView);
    root->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    rootObject = root->rootObject();
}

void Root::resize(const QRect &rect)
{
    QWidget::resize(rect.width(), rect.height());
    root->resize(rect.width(), rect.height());
}

/*! \class Preview
 *  \inmodule Common Print Dialog
 *
 *  Preview class creates a widget to display the preview of the print job
 */

/*!
 *  \fn Preview::Preview(QPrinter *_printer, QWidget *parent)
 *
 *  Constructs Preview objects with \a parent as the parent widget and \a _printer as the printer.
 *  The \a _printer is used further to change the job options that get reflected in the preview.
 */
Preview::Preview(QPrinter *_printer, QString uniqueID, QWidget *parent) :
    QWidget(parent),
    printer(_printer),
    preview(new QPrintPreviewWidget(printer, this))
{
    preview->setGeometry(0, 0, 380, 408);
    preview->fitInView();

    printer->setPaperSize(QPrinter::A4);
    printer->setOrientation(QPrinter::Portrait);

    uniqueID.prepend("/tmp/");
    uniqueID.append(".pdf");

    printer->setOutputFileName(uniqueID);
    printer->setOutputFormat(QPrinter::NativeFormat);

    QObject::connect(preview,
                     SIGNAL(paintRequested(QPrinter *)),
                     this,
                     SLOT(print(QPrinter *)));
}

void Preview::resize(const QRect &rect)
{
    QWidget::resize(rect.width(), rect.height());
    preview->resize(rect.width(), rect.height());
}

/*!
 * \fn void Preview::print(QPrinter *printer)
 *
 *  The function acts as a slot for the paintRequested signal emitted by QPrintPreviewWidget.
 *  The function uses poppler and \a printer settings to generated and paint the image.
 */
void Preview::print(QPrinter *printer)
{
    painter.begin(printer);

    painter.setFont(QFont("Helvetica", 24, QFont::Bold, true));
    painter.drawText(printer->pageRect(), Qt::AlignCenter, tr("Sample Preivew"));

    painter.end();
}

void Preview::setOrientation(const QString &orientation)
{
    if (orientation.compare("portrait") == 0)
        printer->setOrientation(QPrinter::Portrait);
    else if (orientation.compare("landscape") == 0)
        printer->setOrientation(QPrinter::Landscape);
    else qDebug() << "Unhandled Orientation:" << orientation;

    preview->updatePreview();
}

void Preview::setPageSize(QString name, qreal width, qreal height, QString unit)
{
    QPageSize::Unit pageSizeUnit = QPageSize::Unit::Inch;
    if (unit.compare("in") == 0)
        pageSizeUnit = QPageSize::Unit::Inch;
    else if (unit.compare("mm") == 0)
        pageSizeUnit = QPageSize::Unit::Millimeter;
    else
        qDebug() << "Unhandled Unit in Paper Size:" << unit;

    printer->setPageSize(QPageSize(QSizeF(width, height),
                                   pageSizeUnit,
                                   name,
                                   QPageSize::SizeMatchPolicy::FuzzyMatch));

    preview->updatePreview();
}

void Preview::setNumCopies(int copies)
{
    printer->setNumCopies(copies);
    preview->updatePreview();
}

void Preview::setCollateCopies(bool enabled)
{
    printer->setCollateCopies(enabled);
    preview->updatePreview();
}

void Preview::setPrintRange(QString pageRange)
{
    Q_UNUSED(pageRange);
}

void Preview::printfile()
{
    //painter.end();
}

/*!
 *  \fn void Preview::setZoom(qreal zoomFactor)
 *
 *  This function acts as a slot for the zoomSliderValueChanged signal emitted from
 *  pages/preview_toolbar.qml and sets the size of the page shown in the preview according to the
 *  \a zoomFactor.
 */
void Preview::setZoom(qreal zoomFactor)
{
    if (!zoomChanged) {
        // Sets the base zoom factor if zoom has not been changed
        baseZoomFactor = preview->zoomFactor();
        zoomChanged = true;
    }
    /* Whenever zoom slider changes, it rescales it down to
     * baseZoomFactor and then zoom in to the desired amount.
     */
    preview->setZoomFactor(baseZoomFactor);
    preview->zoomIn(zoomFactor);
}

/*!
 * \fn void Preview::showNextPage()
 *
 *  This function acts as a slot for the nextPageButtonClicked signal emitted from
 *  pages/preview_toolbar.qml and shows the next page in the document in the preview window.
 */
void Preview::showNextPage()
{
    pageNumber = pageNumber < (pageCount - 1) ? pageNumber + 1 : pageNumber;
    preview->updatePreview();
}

/*!
 * \fn void Preview::showPrevPage()
 *
 *  This function acts as a slot for the prevPageButtonClicked signal emitted from
 *  pages/preview_toolbar.qml and shows the previous page in the document in the preview window.
 */
void Preview::showPrevPage()
{
    pageNumber = pageNumber > 0 ? pageNumber - 1 : pageNumber;
    preview->updatePreview();
}

/*! \class Controls
 *  \inmodule Common Print Dialog
 *
 *  Controls class creates a QQuickWidget from Controls.qml which contains buttons "Print", "Cancel"
 *  and buttons to show next page, previous page and set zoom of the preview.
 */

/*!
 * \fn Controls::Controls(QWidget *parent)
 *
 *  Constructs Preview objects with \a parent as the parent widget.
 */
Controls::Controls(QWidget *parent) :
    QWidget(parent),
    controls(new QQuickWidget(QUrl("qrc:/Controls.qml"), this))
{

    controls->setResizeMode(QQuickWidget::SizeRootObjectToView);
    controls->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    rootObject = controls->rootObject();
}

void Controls::resize(const QRect &rect)
{
    QWidget::resize(rect.width(), rect.height());
    controls->resize(rect.width(), rect.height());
}
