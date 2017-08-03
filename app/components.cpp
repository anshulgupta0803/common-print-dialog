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
    preview->fitToWidth();

    printer->setPaperSize(QPrinter::Letter);
    printer->setOrientation(QPrinter::Portrait);
    printer->setFullPage(false);

    QObject::connect(preview,
                     SIGNAL(paintRequested(QPrinter *)),
                     this,
                     SLOT(print()));
}

void Preview::print()
{
    QPainter painter(printer);
    painter.setRenderHints(QPainter::Antialiasing |
                           QPainter::TextAntialiasing |
                           QPainter::SmoothPixmapTransform);

    QFile f;
    f.setFileName(":/test.pdf");
    f.open(QIODevice::ReadOnly);
    QByteArray pdf = f.readAll();

    Poppler::Document *document = Poppler::Document::loadFromData(pdf);
    if (!document)
        qCritical("File '%s' does not exist!", qUtf8Printable(":/test.pdf"));
    if (document->isLocked())
        qCritical("File %s is locked!", qUtf8Printable(":/test.pdf"));

    pageCount = document->numPages();

    Poppler::Page *page = document->page(pageNumber);
    if (page == nullptr)
        qCritical("File '%s' is empty?", qUtf8Printable(":/test.pdf"));

    QImage image = page->renderToImage(72.0, 72.0, 0, 0, page->pageSize().width(),
                                       page->pageSize().height());
    if (image.isNull())
        qCritical("Error!");

    paperHeight = page->pageSize().height();
    previewPainted = true;

    painter.drawImage(0, 0, image, 0, 0, 0, 0, 0);
    painter.end();
}

void Preview::setZoom(qreal zoomFactor)
{
    if (previewPainted)
        preview->setZoomFactor(zoomFactor  * (widgetHeight / paperHeight));
    preview->updatePreview();
    currentZoomFactor = zoomFactor;
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
