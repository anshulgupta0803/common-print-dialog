#include "preview.h"
#include <poppler/qt5/poppler-qt5.h>
#include <QMessageLogger>
#include <QDebug>
#include <QFile>

/* The preview works by using poppler to convert a page of pdf to QImage */

QImage QPdfPreview::requestImage(const QString &id, QSize *size, const QSize &requested_size) {
    QString filename;
    QStringList imagesource = id.split("/");
    QStringList::iterator it;
    for (it = imagesource.begin(); it != imagesource.end() - 2; it++)
        filename += "/" + *it;

    // TODO: Remove this line
    QFile::copy(":/test.pdf", filename);

    int pageNumber = (*it).toInt();
    it++;

    QString orientation = *it;
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
    if (orientation.compare("Portrait") == 0)
        image = page->renderToImage(72.0, 72.0, 0, 0, width, height, Poppler::Page::Rotate0);
    else if (orientation.compare("Landscape") == 0)
        image = page->renderToImage(72.0, 72.0, 0, 0, height, width, Poppler::Page::Rotate90);


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
