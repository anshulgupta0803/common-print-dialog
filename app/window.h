#ifndef WINDOW_H
#define WINDOW_H

#include <QGridLayout>
#include <QQuickItem>
#include <QQuickWidget>
#include <QPrintPreviewWidget>
#include <QPainter>
#include <memory>
#include <poppler/qt5/poppler-qt5.h>

#include <QDebug>

extern "C" {
    #include "../backends/cups/src/CPD.h"
    #include "../backends/cups/src/print_frontend.h"
}

class QPrinter;

static int add_printer_callback(PrinterObj *p);
static int remove_printer_callback(char *printer_name);
void ui_add_printer_aux(gpointer key, gpointer value, gpointer user_data);

typedef struct {
    std::string command;
    std::string arg1;
    std::string arg2;
} Command;

class Tabs : public QWidget {
    Q_OBJECT
public:
    QQuickItem* rootObject;
    Tabs(QWidget* parent = Q_NULLPTR);
    ~Tabs() = default;
    void resize(const QRect& rect);

private:
    QQuickWidget* tabs;
};

class Root : public QWidget {
    Q_OBJECT
public:
    QQuickItem* rootObject;
    Root(QWidget* parent = Q_NULLPTR);
    ~Root() = default;
    void resize(const QRect& rect);

private:
    QQuickWidget* root;
};

class Preview : public QWidget {
    Q_OBJECT
public:
    Preview(QWidget* parent = Q_NULLPTR);
    ~Preview() = default;
    qreal widgetHeight = 0;
    qreal currentZoomFactor = 1;

public Q_SLOTS:
    void print(QPrinter* printer);
    void setZoom(qreal zoomFactor);
    void showNextPage();
    void showPrevPage();

private:
    std::unique_ptr<QPrinter> printer;
    QPrintPreviewWidget* preview;
    int pageNumber = 0;
    int pageCount = 0;
    qreal paperHeight = 0;
    bool previewPainted = 0;
};

class Controls : public QWidget {
    Q_OBJECT
public:
    QQuickItem* rootObject;
    Controls(QWidget* parent = Q_NULLPTR);
    ~Controls() = default;
    void resize(const QRect& rect);

private:
    QQuickWidget* controls;
};

class _Window : public QWidget {
    Q_OBJECT
public:
    FrontendObj *f;
    GMainLoop *loop;
    Tabs* tabs;
    Root* root;
    Preview* preview;
    Controls* controls;
    QGridLayout* masterLayout;

    _Window(QWidget* parent = Q_NULLPTR);
    void init_backend();
    void addPrinter(const char* printer);
    void clearPrinters();
    void addPrinterSupportedMedia(char* media) {}
    void clearPrintersSupportedMedia() {}
    void addMaximumPrintCopies(int copies) {}
    void addJobHoldUntil(char* startJobOption) {}
    void addPagesPerSize(char* pages) {}
    void updateAllOptions(const QString &printer) {}
    gpointer parse_commands(gpointer user_data);
    gpointer ui_add_printer(gpointer user_data);

public Q_SLOTS:
    void tabBarIndexChanged(qint32 index);
    void swipeViewIndexChanged(qint32 index);
    void cancelButtonClicked();
};

class Window : public QWidget {
public:
    Window(QWidget *parent = Q_NULLPTR);

protected:
    void resizeEvent(QResizeEvent* event) override;
};

#endif // WINDOW_H
