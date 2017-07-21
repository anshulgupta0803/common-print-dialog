#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QQuickItem>
#include <QQuickWidget>
#include <QPrintPreviewWidget>
#include <QPainter>
#include <memory>
#include <poppler/qt5/poppler-qt5.h>

class QPrinter;
class QVBoxLayout;

class Tabs : public QWidget {
    Q_OBJECT
public:
    QQuickItem* rootObject;
    Tabs(QWidget* parent = Q_NULLPTR);
    ~Tabs() = default;
    void resize(const QRect& rect);

private:
    QQuickWidget* tabs;
};

class Root : public QWidget {
    Q_OBJECT
public:
    QQuickItem* rootObject;
    Root(QWidget* parent = Q_NULLPTR);
    ~Root() = default;
    void resize(const QRect& rect);

private:
    QQuickWidget* root;
};

class Preview : public QWidget {
    Q_OBJECT
public:
    Preview(QWidget* parent = Q_NULLPTR);
    ~Preview() = default;
    qreal widgetHeight = 0;
    qreal currentZoomFactor = 1;

public Q_SLOTS:
    void print(QPrinter* printer);
    void setZoom(qreal zoomFactor);
    void showNextPage();
    void showPrevPage();

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
    Controls(QWidget* parent = Q_NULLPTR);
    ~Controls() = default;
    void resize(const QRect& rect);

private:
    QQuickWidget* controls;
};

class Window : public QMainWindow {
    Q_OBJECT
public:
    Window();

public Q_SLOTS:
    void tabBarIndexChanged(qint32 index);
    void swipeViewIndexChanged(qint32 index);
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
