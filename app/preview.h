#ifndef PREVIEW_H
#define PREVIEW_H

#include <QQuickImageProvider>

class pdf_preview : public QQuickImageProvider{
public:
    pdf_preview() : QQuickImageProvider(QQuickImageProvider::Image){}
    QImage requestImage(const QString &id, QSize *size, const QSize &requested_size);
};

#endif // PREVIEW_H
