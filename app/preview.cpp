#include "preview.h"
#include <poppler/qt5/poppler-qt5.h>
#include <QMessageLogger>
#include <QDebug>

/* The preview works by using poppler to convert a page of pdf to QImage */

QImage QPdfPreview::requestImage(const QString &id, QSize *size, const QSize &requested_size) {
    int filenameLength = id.lastIndexOf("/");
    QString filename = "/" + id.mid(0, filenameLength);
    int pageNumber = id.mid(filenameLength + 1, id.size()).toInt();
    QImage image;

    Poppler::Document *document = Poppler::Document::load(filename);
    if (!document || document->isLocked()){
        qCritical("File '%s' does not exist or is locked!", qUtf8Printable(filename));
        return image;
    }

    Poppler::Page *page = document->page(pageNumber);
    if (page == nullptr){
        qCritical("File '%s' is empty?", qUtf8Printable(filename));
        return image;
    }

    int height = page->pageSize().height();
    int width = page->pageSize().width();
    image = page->renderToImage(72.0, 72.0, 0, 0, width, height);


    if (image.isNull())
        qCritical("Error!");

    return image;
}

int QPreviewData::get_number_of_pages(QString filename){
    Poppler::Document *document = Poppler::Document::load(filename);
    if (!document || document->isLocked()){
        qCritical("File '%s' does not exist or is locked!", qUtf8Printable(filename));
        return 0;
    }

    return document->numPages();
}
