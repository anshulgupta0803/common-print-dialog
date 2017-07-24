#include "window.h"
#include <QDebug>

_Window *_window;

_Window::_Window(QWidget *parent) :
    QWidget(parent),
    masterLayout(new QGridLayout(this)),
    tabs(new Tabs(this)),
    root(new Root(this)),
    preview(new Preview(this)),
    controls(new Controls(this))
{
    /*
     * masterLayout
     * |-tabs
     * |-root -- preview
     * |-controls
     */
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

    preview->widgetHeight = masterLayout->itemAt(2)->geometry().height();

    adjustSize();

    setMaximumSize(700, 480);
    setMinimumSize(700, 480);

    init_backend();
}

Window::Window(QWidget *parent) :
    QWidget(parent)
{
    _window = new _Window(parent);
    _window->show();
}

void Window::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
//    _window->tabs->resize(_window->container->itemAt(0)->geometry());
//    _window->root->resize(_window->content->itemAt(0)->geometry());
//    _window->controls->resize(_window->container->itemAt(2)->geometry());
//    _window->preview->widgetHeight = _window->content->itemAt(1)->geometry().height();
//    _window->preview->setZoom(_window->preview->currentZoomFactor);
}

void _Window::tabBarIndexChanged(qint32 index) {
    root->rootObject->setProperty("index", index);
}

void _Window::swipeViewIndexChanged(qint32 index) {
    tabs->rootObject->setProperty("index", index);
}

void _Window::cancelButtonClicked() {
    exit(0);
}

static int add_printer_callback(PrinterObj *p) {
    printf("print_frontend.c : Printer %s added!\n", p->name);
}

static int remove_printer_callback(char *printer_name) {
    printf("print_frontend.c : Printer %s removed!\n", printer_name);
}

gpointer _Window::ui_add_printer(gpointer user_data) {
    /*
     * Need this delay so that the FrontendObj
     * initialization completes
    */
    bool* enabled = (bool*)user_data;
    for (int i = 0; i < 100000000; i++);
    Command cmd;
    if (*enabled) {
        cmd.command = "unhide-remote-cups";
        parse_commands(&cmd);
    }
    else {
        cmd.command = "hide-remote-cups";
        parse_commands(&cmd);
    }
    clearPrinters();
    g_hash_table_foreach(f->printer, ui_add_printer_aux, NULL);
}

void ui_add_printer_aux(gpointer key, gpointer value, gpointer user_data) {
    _window->addPrinter((const char*)key);
    qDebug() << "Added" << (const char*)key;
}

void _Window::addPrinter(const char *printer) {
    QObject* obj = root->rootObject->findChild<QObject*>("generalObject");
    if (obj) {
        QMetaObject::invokeMethod(obj,
                                  "updateDestinationModel",
                                  Q_ARG(QVariant, printer));
    }
    else
        qDebug() << "generalObject Not Found";
}

gpointer _Window::parse_commands(gpointer user_data) {
    Command* cmd = (Command*)user_data;
    if (cmd->command.compare("hide-remote-cups") == 0)
        hide_remote_cups_printers(f);
    else if (cmd->command.compare("unhide-remote-cups") == 0)
        unhide_remote_cups_printers(f);
    else if (cmd->command.compare("get-all-options") == 0) {
        char printerName[300];
        strcpy(printerName, cmd->arg1.c_str());
        get_all_printer_options(_window->f, printerName);
    }
}

void _Window::init_backend() {
    event_callback add_cb = (event_callback)add_printer_callback;
    event_callback rem_cb = (event_callback)remove_printer_callback;
    f = get_new_FrontendObj(NULL, add_cb, rem_cb);
    bool enabled = true;
    //g_thread_new("add_printer_thread", (GThreadFunc)ui_add_printer, &enabled);
    ui_add_printer(&enabled);
    connect_to_dbus(f);
    loop = g_main_loop_new(NULL, FALSE);
    //g_main_loop_run(loop);
}

void _Window::clearPrinters() {
//    QObject* obj = root->rootObject->findChild<QObject*>("generalObject");
//    if (obj) {
//        QMetaObject::invokeMethod(obj,
//                                  "clearDestinationModel");
//    }
//    else
//        qDebug() << "generalObject Not Found";
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

void ui_add_job_hold_until(char *startJobOption) {}

void ui_add_maximum_print_copies(char *_copies) {}

void ui_add_pages_per_side(char *pages) {}

void ui_clear_supported_media() {}

void ui_add_supported_media(char *media) {}
