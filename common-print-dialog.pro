QT += qml quick widgets quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

TARGET = QCPDialog
TEMPLATE = lib

CONFIG += c++11 no_keywords
unix {
    target.path = /usr/lib
    headerfiles.path = /usr/include/common-print-dialog
    headerfiles.files = $$PWD/app/*.h
    INSTALLS += target headerfiles
    CONFIG += link_pkgconfig
    PKGCONFIG += CPDFrontend gio-unix-2.0 glib-2.0 gobject-2.0 poppler-qt5
}

SOURCES += \
    app/components.cpp \
    app/QCPDialog.cpp

HEADERS += \
    app/components.h \
    app/QCPDialog.h \
    app/QCPDialog_global.h

RESOURCES += app/qml.qrc
DEFINES += QCPDIALOG_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
