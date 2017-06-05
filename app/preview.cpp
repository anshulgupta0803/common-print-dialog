#include "preview.h"
#include <poppler/qt5/poppler-qt5.h>
#include <iostream>

using namespace std;

/* The preview works by using poppler to convert a page of pdf to QImage */

QImage QPdfPreview::requestImage(const QString &id, QSize *size, const QSize &requested_size) {
    int filenameLength = id.size() - id.indexOf("/") + 1;
    QString filename = "/" + id.mid(0, filenameLength);
    int pageNumber = id.mid(filenameLength + 1, id.size()).toInt();

    Poppler::Document *document = Poppler::Document::load(filename);
    if (!document || document->isLocked())
        cout << "ERROR1" << endl;
    
    Poppler::Page *page = document->page(pageNumber);
    if (page == nullptr)
        cout << "ERROR2" << endl;

    QImage image = page->renderToImage(72.0, 72.0, 0, 0, page->pageSize().width(), page->pageSize().height());
    if (image.isNull())
        cout << "ERROR3" << endl;

    return image;
}
