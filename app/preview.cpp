#include "preview.h"
#include <poppler/qt5/poppler-qt5.h>
#include <iostream>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>

using namespace std;

/* The preview works by using poppler to convert a page of pdf to QImage */

QImage QPdfPreview::requestImage(const QString &id, QSize *size, const QSize &requested_size) {
    int filenameLength = id.lastIndexOf("/");
    QString filename = "/" + id.mid(0, filenameLength);
    int pageNumber = id.mid(filenameLength + 1, id.size()).toInt();
    QImage image;

    Poppler::Document *document = Poppler::Document::load(filename);
    if (document && !document->isLocked()) {

        Poppler::Page *page = document->page(pageNumber);
        if (page != nullptr) {
            image = page->renderToImage(72.0, 72.0, 0, 0, page->pageSize().width(), page->pageSize().height());
            if (image.isNull())
                cout << "ERROR3" << endl;
        }
//        else {
//            QQuickView view;
//            view.setSource(QUrl::fromLocalFile("PreviewForm.ui.qml"));
//            QQuickItem *item = view.rootObject()->findChild<QQuickItem*>("image");
//            if (item)
//                item->setProperty("source", "Hello");
//            else
//                cout << "Error" << endl;
//        }
    }

    return image;
}
