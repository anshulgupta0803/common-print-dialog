/****************************************************************************
**
**  $QT_BEGIN_LICENSE:GPL$
**
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>
**
**  $QT_END_LICENSE$
**
****************************************************************************/

#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <QQuickItem>
#include <QQuickWidget>
#include <QPrintPreviewWidget>
#include <QPrinter>

#include <QPainter>

class Tabs : public QWidget
{
    Q_OBJECT
public:
    QQuickItem *rootObject;
    Tabs(QWidget *parent = Q_NULLPTR);
    ~Tabs() = default;
    void resize(const QRect &rect);

private:
    QQuickWidget *tabs;
};

class Root : public QWidget
{
    Q_OBJECT
public:
    QQuickItem *rootObject;
    Root(QWidget *parent = Q_NULLPTR);
    ~Root() = default;
    void resize(const QRect &rect);

private:
    QQuickWidget *root;
};

class Preview : public QWidget
{
    Q_OBJECT
public:
    Preview(QPrinter *_printer, QString uniqueID, QWidget *parent = Q_NULLPTR);
    ~Preview() = default;
    void resize(const QRect &rect);
    void setOrientation(const QString &orientation);
    void setPageSize(QString name, qreal width, qreal height, QString unit);
    void setNumCopies(int copies);
    void setCollateCopies(bool enabled);
    void setPrintRange(QString pageRange);
    void printfile();

public Q_SLOTS:
    void print(QPrinter *printer);
    void setZoom(qreal zoomFactor);
    void showNextPage();
    void showPrevPage();

private:
    QPrinter *printer;
    QPainter painter;
    QPrintPreviewWidget *preview;
    int pageNumber = 0;
    int pageCount = 0;
    qreal baseZoomFactor = 0;
    bool zoomChanged = false;
};

class Controls : public QWidget
{
    Q_OBJECT
public:
    QQuickItem *rootObject;
    Controls(QWidget *parent = Q_NULLPTR);
    ~Controls() = default;
    void resize(const QRect &rect);

private:
    QQuickWidget *controls;
};


#endif // COMPONENTS_H
