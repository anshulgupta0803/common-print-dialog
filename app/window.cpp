#include "window.h"
#include <QDebug>

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

void Window::cancelButtonClicked() {
    exit(0);
}
