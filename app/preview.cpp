#include "preview.h"
#include <poppler/qt5/poppler-qt5.h>
#include <QMessageLogger>
#include <QDebug>
#include <QFile>
#include <QPageSize>

/* The preview works by using poppler to convert a page of pdf to QImage */

QImage QPdfPreview::requestImage(const QString &id, QSize *size, const QSize &requested_size) {
    QString filename;
    QStringList imagesource = id.split("/");
    QStringList::iterator it;
    for (it = imagesource.begin(); it != imagesource.end() - 3; it++)
        filename += "/" + *it;

    // TODO: Remove this line
    QFile::copy(":/app/test.pdf", filename);

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

    int height, width;
    QPreviewData data;
    QSizeF pageSize = data.getPageSize(paper);
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

QSizeF QPreviewData::getPageSize(QString page) {
    /*
     * Need to come up with a different logic
     * This will return page size of A1 for A10 or
     * page size of A4 for A4 Extra and so on
    */
    if (page.contains("A0", Qt::CaseInsensitive))
        return QPageSize::size(QPageSize::PageSizeId::A0, QPageSize::Unit::Point);
    else if (page.contains("A1", Qt::CaseInsensitive))
        return QPageSize::size(QPageSize::PageSizeId::A1, QPageSize::Unit::Point);
    else if (page.contains("A2", Qt::CaseInsensitive))
        return QPageSize::size(QPageSize::PageSizeId::A2, QPageSize::Unit::Point);
    else if (page.contains("A4", Qt::CaseInsensitive))
        return QPageSize::size(QPageSize::PageSizeId::A4, QPageSize::Unit::Point);
    else if (page.contains("A5", Qt::CaseInsensitive))
        return QPageSize::size(QPageSize::PageSizeId::A5, QPageSize::Unit::Point);
    else if (page.contains("A6", Qt::CaseInsensitive))
        return QPageSize::size(QPageSize::PageSizeId::A6, QPageSize::Unit::Point);
    else if (page.contains("A7", Qt::CaseInsensitive))
        return QPageSize::size(QPageSize::PageSizeId::A7, QPageSize::Unit::Point);
    else if (page.contains("A8", Qt::CaseInsensitive))
        return QPageSize::size(QPageSize::PageSizeId::A8, QPageSize::Unit::Point);
    else if (page.contains("A9", Qt::CaseInsensitive))
        return QPageSize::size(QPageSize::PageSizeId::A9, QPageSize::Unit::Point);
    else if (page.contains("B0", Qt::CaseInsensitive))
        return QPageSize::size(QPageSize::PageSizeId::B0, QPageSize::Unit::Point);
    else if (page.contains("B1", Qt::CaseInsensitive))
        return QPageSize::size(QPageSize::PageSizeId::B1, QPageSize::Unit::Point);
    else if (page.contains("B2", Qt::CaseInsensitive))
        return QPageSize::size(QPageSize::PageSizeId::B2, QPageSize::Unit::Point);
    else if (page.contains("B3", Qt::CaseInsensitive))
        return QPageSize::size(QPageSize::PageSizeId::B3, QPageSize::Unit::Point);
    else if (page.contains("B4", Qt::CaseInsensitive))
        return QPageSize::size(QPageSize::PageSizeId::B4, QPageSize::Unit::Point);
    else if (page.contains("B5", Qt::CaseInsensitive))
        return QPageSize::size(QPageSize::PageSizeId::B5, QPageSize::Unit::Point);
    else if (page.contains("B6", Qt::CaseInsensitive))
        return QPageSize::size(QPageSize::PageSizeId::B6, QPageSize::Unit::Point);
    else if (page.contains("B7", Qt::CaseInsensitive))
        return QPageSize::size(QPageSize::PageSizeId::B7, QPageSize::Unit::Point);
    else if (page.contains("B8", Qt::CaseInsensitive))
        return QPageSize::size(QPageSize::PageSizeId::B8, QPageSize::Unit::Point);
    else if (page.contains("B9", Qt::CaseInsensitive))
        return QPageSize::size(QPageSize::PageSizeId::B9, QPageSize::Unit::Point);
    else if (page.contains("B10", Qt::CaseInsensitive))
        return QPageSize::size(QPageSize::PageSizeId::B10, QPageSize::Unit::Point);
    else if (page.contains("B4", Qt::CaseInsensitive))
        return QPageSize::size(QPageSize::PageSizeId::B4, QPageSize::Unit::Point);
    else if (page.contains("EnvC5", Qt::CaseInsensitive))
        return QPageSize::size(QPageSize::PageSizeId::C5E, QPageSize::Unit::Point);
    else if (page.contains("Comm10E", Qt::CaseInsensitive))
        return QPageSize::size(QPageSize::PageSizeId::Comm10E, QPageSize::Unit::Point);
    else if (page.contains("EnvDL", Qt::CaseInsensitive))
        return QPageSize::size(QPageSize::PageSizeId::DLE, QPageSize::Unit::Point);
    else if (page.contains("Executive", Qt::CaseInsensitive))
        return QPageSize::size(QPageSize::PageSizeId::Executive, QPageSize::Unit::Point);
    else if (page.contains("Folio", Qt::CaseInsensitive))
        return QPageSize::size(QPageSize::PageSizeId::Folio, QPageSize::Unit::Point);
    else if (page.contains("Ledger", Qt::CaseInsensitive))
        return QPageSize::size(QPageSize::PageSizeId::Ledger, QPageSize::Unit::Point);
    else if (page.contains("Legal", Qt::CaseInsensitive))
        return QPageSize::size(QPageSize::PageSizeId::Legal, QPageSize::Unit::Point);
    else if (page.contains("B4", Qt::CaseInsensitive))
        return QPageSize::size(QPageSize::PageSizeId::B4, QPageSize::Unit::Point);
    else if (page.contains("Letter", Qt::CaseInsensitive))
        return QPageSize::size(QPageSize::PageSizeId::Letter, QPageSize::Unit::Point);
    else if (page.contains("Tabloid", Qt::CaseInsensitive))
        return QPageSize::size(QPageSize::PageSizeId::Tabloid, QPageSize::Unit::Point);
    else if (page.contains("B4", Qt::CaseInsensitive))
        return QPageSize::size(QPageSize::PageSizeId::B4, QPageSize::Unit::Point);
    else if (page.contains("Custom", Qt::CaseInsensitive))
        return QPageSize::size(QPageSize::PageSizeId::Custom, QPageSize::Unit::Point);
    else return QSizeF(100, 100);
}
