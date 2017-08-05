#include "components.h"
#include <poppler/qt5/poppler-qt5.h>

Tabs::Tabs(QWidget *parent) :
    QWidget(parent),
    tabs(new QQuickWidget(QUrl("qrc:/Tabs.qml"), this))
{

    tabs->setResizeMode(QQuickWidget::SizeRootObjectToView);
    tabs->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    rootObject = tabs->rootObject();
}

Root::Root(QWidget *parent) :
    QWidget(parent),
    root(new QQuickWidget(QUrl("qrc:/Root.qml"), this))
{

    root->setResizeMode(QQuickWidget::SizeRootObjectToView);
    root->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    rootObject = root->rootObject();
}
Preview::Preview(QPrinter *_printer, QWidget *parent) :
    QWidget(parent),
    printer(_printer),
    preview(new QPrintPreviewWidget(printer, this))
{
    preview->setGeometry(0, 0, 380, 408);
    preview->fitInView();

    printer->setPaperSize(QPrinter::A4);
    printer->setOrientation(QPrinter::Portrait);

    QObject::connect(preview,
                     SIGNAL(paintRequested(QPrinter *)),
                     this,
                     SLOT(print(QPrinter *)));
}

void Preview::print(QPrinter *printer)
{
    QPainter painter;
    painter.begin(printer);

    painter.setRenderHints(QPainter::Antialiasing |
                           QPainter::TextAntialiasing |
                           QPainter::SmoothPixmapTransform);

    QString text{"Hello World!"};
    QRect rect({100, 100}, QSize{500, 500});
    painter.drawText(rect, Qt::AlignLeft | Qt::AlignTop, text);
    painter.drawEllipse(rect);
    painter.end();

//    QFile f;
//    f.setFileName(":/test.pdf");
//    f.open(QIODevice::ReadOnly);
//    QByteArray pdf = f.readAll();

//    Poppler::Document *document = Poppler::Document::loadFromData(pdf);
//    if (!document)
//        qCritical("File '%s' does not exist!", qUtf8Printable(":/test.pdf"));
//    if (document->isLocked())
//        qCritical("File %s is locked!", qUtf8Printable(":/test.pdf"));

//    pageCount = document->numPages();

//    Poppler::Page *page = document->page(pageNumber);
//    if (page == nullptr)
//        qCritical("File '%s' is empty?", qUtf8Printable(":/test.pdf"));

//    QImage image = page->renderToImage(72.0, 72.0, 0, 0, page->pageSize().width(),
//                                       page->pageSize().height());
//    if (image.isNull())
//        qCritical("Error!");

//    painter.drawImage(0, 0, image, 0, 0, 0, 0, 0);
//    painter.end();
}

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

void Preview::showNextPage()
{
    pageNumber = pageNumber < (pageCount - 1) ? pageNumber + 1 : pageNumber;
    preview->updatePreview();
}

void Preview::showPrevPage()
{
    pageNumber = pageNumber > 0 ? pageNumber - 1 : pageNumber;
    preview->updatePreview();
}

Controls::Controls(QWidget *parent) :
    QWidget(parent),
    controls(new QQuickWidget(QUrl("qrc:/Controls.qml"), this))
{

    controls->setResizeMode(QQuickWidget::SizeRootObjectToView);
    controls->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    rootObject = controls->rootObject();
}
