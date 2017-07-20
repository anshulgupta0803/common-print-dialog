#include "window.h"

Window::Window() :
    tabs(new Tabs(this)),
    content(new QHBoxLayout()),
    root(new Root(this)),
    preview(new Preview(this)),
    controls(new Controls(this)),
    container(new QVBoxLayout())
{
    /*
     * container
     * |-tabs
     * |-content
     *   |-root
     *   |-preview
     * |-controls
     */
    setCentralWidget(new QWidget(this));

    tabs->setMinimumSize(700, 32);
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

    content->setSpacing(0);
    content->setMargin(0);

    root->setMinimumSize(320, 408);

    preview->setMinimumSize(380, 408);

    content->addWidget(root);
    content->addWidget(preview);

    controls->setMinimumSize(700, 40);

    container->setSpacing(0);
    container->setMargin(0);
    container->addWidget(tabs);
    container->addLayout(content);
    container->addWidget(controls);

    preview->widgetHeight = content->itemAt(1)->geometry().height();

    centralWidget()->setLayout(container);
    adjustSize();
}

void Window::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    tabs->resize(container->itemAt(0)->geometry());
    root->resize(content->itemAt(0)->geometry());
    controls->resize(container->itemAt(2)->geometry());
    preview->widgetHeight = content->itemAt(1)->geometry().height();
    preview->setZoom(preview->currentZoomFactor);
}

void Window::tabBarIndexChanged(qint32 index) {
    root->rootObject->setProperty("index", index);
}

void Window::swipeViewIndexChanged(qint32 index) {
    tabs->rootObject->setProperty("index", index);
}

void Window::cancelButtonClicked() {
    exit(0);
}

Tabs::Tabs(QWidget* parent) :
    QWidget(parent),
    tabs(new QQuickWidget(QUrl("qrc:/app/Tabs.qml"), this)) {

    tabs->setResizeMode(QQuickWidget::SizeRootObjectToView);
    tabs->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    rootObject = tabs->rootObject();
}

void Tabs::resize(const QRect& rect) {
    QWidget::resize(rect.width(), rect.height());
    tabs->resize(rect.width(), rect.height());
}

Root::Root(QWidget* parent) :
    QWidget(parent),
    root(new QQuickWidget(QUrl("qrc:/app/Root.qml"), this)) {

    root->setResizeMode(QQuickWidget::SizeRootObjectToView);
    root->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    rootObject = root->rootObject();
}

void Root::resize(const QRect& rect) {
    QWidget::resize(rect.width(), rect.height());
    root->resize(rect.width(), rect.height());
}

Preview::Preview(QWidget* parent) :
    QWidget(parent),
    printer(new QPrinter{}),
    preview(new QPrintPreviewWidget(printer.get(), this))
{
    printer->setPaperSize(QPrinter::Letter);
    printer->setOrientation(QPrinter::Portrait);
    printer->setFullPage(false);

    QObject::connect(preview,
                     SIGNAL(paintRequested(QPrinter*)),
                     this,
                     SLOT(print(QPrinter*)));
}

void Preview::print(QPrinter* printer) {
    QPainter painter(printer);
    painter.setRenderHints(QPainter::Antialiasing |
                           QPainter::TextAntialiasing |
                           QPainter::SmoothPixmapTransform);

    QFile f;
    f.setFileName(":/app/test.pdf");
    f.open(QIODevice::ReadOnly);
    QByteArray pdf=f.readAll();

    Poppler::Document *document = Poppler::Document::loadFromData(pdf);
    if (!document)
        qCritical("File '%s' does not exist!", qUtf8Printable(":/app/test.pdf"));
    if (document->isLocked())
        qCritical("File %s is locked!", qUtf8Printable(":/app/test.pdf"));

    pageCount = document->numPages();

    Poppler::Page *page = document->page(pageNumber);
    if (page == nullptr)
        qCritical("File '%s' is empty?", qUtf8Printable(":/app/test.pdf"));

    QImage image = page->renderToImage(72.0, 72.0, 0, 0, page->pageSize().width(), page->pageSize().height());
    if (image.isNull())
        qCritical("Error!");

    paperHeight = page->pageSize().height();
    previewPainted = true;

    painter.drawImage(0, 0, image, 0, 0, 0, 0, 0);
    painter.end();
}

void Preview::setZoom(qreal zoomFactor) {
    if(previewPainted)
        preview->setZoomFactor(zoomFactor  * (widgetHeight / paperHeight));
    preview->updatePreview();
    currentZoomFactor = zoomFactor;
}

void Preview::showNextPage() {
    pageNumber = pageNumber < (pageCount - 1) ? pageNumber + 1 : pageNumber;
    preview->updatePreview();
}

void Preview::showPrevPage() {
    pageNumber = pageNumber > 0 ? pageNumber - 1 : pageNumber;
    preview->updatePreview();
}

Controls::Controls(QWidget* parent) :
    QWidget(parent),
    controls(new QQuickWidget(QUrl("qrc:/app/Controls.qml"), this)) {

    controls->setResizeMode(QQuickWidget::SizeRootObjectToView);
    controls->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    rootObject = controls->rootObject();
}

void Controls::resize(const QRect& rect) {
    QWidget::resize(rect.width(), rect.height());
    controls->resize(rect.width(), rect.height());
}
