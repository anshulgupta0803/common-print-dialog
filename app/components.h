#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <QQuickItem>
#include <QQuickWidget>
#include <QPrintPreviewWidget>
#include <QPainter>
#include <QPrinter>

class Tabs : public QWidget
{
    Q_OBJECT
public:
    QQuickItem *rootObject;
    Tabs(QWidget *parent = Q_NULLPTR);
    ~Tabs() = default;

private:
    QQuickWidget *tabs;
};

class Root : public QWidget
{
    Q_OBJECT
public:
    QQuickItem *rootObject;
    Root(QWidget *parent = Q_NULLPTR);
    ~Root() = default;

private:
    QQuickWidget *root;
};

class Preview : public QWidget
{
    Q_OBJECT
public:
    Preview(QPrinter *_printer, QWidget *parent = Q_NULLPTR);
    ~Preview() = default;

public Q_SLOTS:
    void print(QPrinter *printer);
    void setZoom(qreal zoomFactor);
    void showNextPage();
    void showPrevPage();

private:
    QPrinter *printer;
    QPrintPreviewWidget *preview;
    int pageNumber = 0;
    int pageCount = 0;
    qreal baseZoomFactor = 0;
    bool zoomChanged = false;
};

class Controls : public QWidget
{
    Q_OBJECT
public:
    QQuickItem *rootObject;
    Controls(QWidget *parent = Q_NULLPTR);
    ~Controls() = default;

private:
    QQuickWidget *controls;
};


#endif // COMPONENTS_H
