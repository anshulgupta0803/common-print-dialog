#include "window.h"

Window::Window() :
    tabs(new Tabs(this)),
    content(new QHBoxLayout()),
    root(new Root(this)),
    controls(new Controls(this)),
    container(new QVBoxLayout())
{

    setCentralWidget(new QWidget(this));

    tabs->setMinimumSize(640, 32);

    content->setSpacing(0);
    content->setMargin(0);

    root->setMinimumSize(320, 408);
    root->setProperty("currentIndex", tabs->property("currentIndex"));
    content->addWidget(root, 100);

    controls->setMinimumSize(640, 40);

    container->setSpacing(0);
    container->setMargin(0);
    container->addWidget(tabs);
    container->addLayout(content);
    container->addWidget(controls);

    centralWidget()->setLayout(container);
    adjustSize();
}

void Window::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    tabs->resize(container->itemAt(0)->geometry());
    controls->resize(container->itemAt(0)->geometry());
}
