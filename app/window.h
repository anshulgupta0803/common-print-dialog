#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QObject>
#include <QQuickItem>
#include <QQmlContext>
#include <QQuickWidget>
#include <QPrintPreviewWidget>
#include <QPrinter>
#include <QPainter>
#include <memory>
#include <poppler/qt5/poppler-qt5.h>
#include <QFile>


class Tabs : public QWidget {
    Q_OBJECT
public:
    QQuickItem* rootObject;
    Tabs(QWidget* parent = Q_NULLPTR) :
        QWidget(parent),
        tabs(new QQuickWidget(QUrl("qrc:/app/Tabs.qml"), this)) {

        tabs->setResizeMode(QQuickWidget::SizeRootObjectToView);
        tabs->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        rootObject = tabs->rootObject();
    }

    ~Tabs() = default;

    void resize(const QRect& rect) {
        QWidget::resize(rect.width(), rect.height());
        tabs->resize(rect.width(), rect.height());
    }

private:
    QQuickWidget* tabs;
};

class Root : public QWidget {
    Q_OBJECT
public:
    QQuickItem* rootObject;
    Root(QWidget* parent = Q_NULLPTR) :
        QWidget(parent),
        root(new QQuickWidget(QUrl("qrc:/app/Root.qml"), this)) {

        root->setResizeMode(QQuickWidget::SizeRootObjectToView);
        root->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        rootObject = root->rootObject();
    }

    ~Root() = default;

    void resize(const QRect& rect) {
        QWidget::resize(rect.width(), rect.height());
        root->resize(rect.width(), rect.height());
    }

private:
    QQuickWidget* root;
};

class Preview : public QWidget {
    Q_OBJECT
public:
    Preview(QWidget* parent = Q_NULLPTR) :
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

    ~Preview() = default;

    qreal widgetHeight = 0;
    qreal currentZoomFactor = 1;

public Q_SLOTS:
    void print(QPrinter* printer) {
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

    void setZoom(qreal zoomFactor) {
        if(previewPainted)
            preview->setZoomFactor(zoomFactor  * (widgetHeight / paperHeight));
        preview->updatePreview();
        currentZoomFactor = zoomFactor;
    }

    void showNextPage() {
        pageNumber = pageNumber < (pageCount - 1) ? pageNumber + 1 : pageNumber;
        preview->updatePreview();
    }

    void showPrevPage() {
        pageNumber = pageNumber > 0 ? pageNumber - 1 : pageNumber;
        preview->updatePreview();
    }

private:
    std::unique_ptr<QPrinter> printer;
    QPrintPreviewWidget* preview;
    int pageNumber = 0;
    int pageCount = 0;
    qreal paperHeight = 0;
    bool previewPainted = 0;
};

class Controls : public QWidget {
    Q_OBJECT
public:
    QQuickItem* rootObject;
    Controls(QWidget* parent = Q_NULLPTR) :
        QWidget(parent),
        controls(new QQuickWidget(QUrl("qrc:/app/Controls.qml"), this)) {

        controls->setResizeMode(QQuickWidget::SizeRootObjectToView);
        controls->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        rootObject = controls->rootObject();
    }

    ~Controls() = default;

    void resize(const QRect& rect) {
        QWidget::resize(rect.width(), rect.height());
        controls->resize(rect.width(), rect.height());
    }

private:
    QQuickWidget* controls;
};

class Window : public QMainWindow {
    Q_OBJECT
public:
    Window();

public Q_SLOTS:
    void tabBarIndexChanged(qint32 index);
    void cancelButtonClicked();

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    Tabs* tabs;
    QHBoxLayout* content;
    Root* root;
    Preview* preview;
    Controls* controls;
    QVBoxLayout* container;
};

#endif // WINDOW_H
