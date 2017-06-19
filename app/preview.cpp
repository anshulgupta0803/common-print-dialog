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
    for (it = imagesource.begin(); it != imagesource.end() - 3; it++)
        filename += "/" + *it;

    // TODO: Remove this line
    QFile::copy(":/test.pdf", filename);

    int pageNumber = (*it).toInt();
    it++;

    QString orientation = *it;
    it++;

    QString paper = *it;

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

    QPreviewData data;
    QSize pageSize;
    pageSize = data.getPageSize(paper);
    height = pageSize.height();
    width = pageSize.width();
    //qDebug() << height << "" << width;
    if (orientation.compare("Portrait") == 0)
        image = page->renderToImage(72.0, 72.0, 0, 0, width, height, Poppler::Page::Rotate0);
    else if (orientation.compare("Landscape") == 0)
        image = page->renderToImage(72.0, 72.0, 0, 0, height, width, Poppler::Page::Rotate0);


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

QSize QPreviewData::getPageSize(QString page) {
    QSize pageSize;
    if (page.compare("A4") == 0) {
        pageSize.rheight() = 842;
        pageSize.rwidth() = 595;
    }

    else if (page.compare("Letter") == 0) {
        pageSize.rheight() = 792;
        pageSize.rwidth() = 612;
    }
    else {
        pageSize.rheight() = 100;
        pageSize.rwidth() = 100;
    }
    return pageSize;
}
