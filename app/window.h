#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets>
#include <QtQuickWidgets/QQuickWidget>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QObject>

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
public:
    Window();

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    Tabs* tabs;
    QHBoxLayout* content;
    Root* root;
    Controls* controls;
    QVBoxLayout* container;
};

#endif // WINDOW_H
