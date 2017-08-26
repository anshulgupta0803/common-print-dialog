QT += qml quick widgets quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

TARGET = QCPDialog
TEMPLATE = lib

CONFIG += c++11 no_keywords
unix {
    target.path = /usr/lib
    headerfiles.path = /usr/include/common-print-dialog
    headerfiles.files = $$PWD/*.h
    INSTALLS += target headerfiles
    CONFIG += link_pkgconfig
    PKGCONFIG += CPDFrontend gio-unix-2.0 glib-2.0 gobject-2.0
}

SOURCES += \
    components.cpp \
    QCPDialog.cpp

HEADERS += \
    components.h \
    QCPDialog.h \
    QCPDialog_global.h \
    singleton.h

RESOURCES += qml.qrc
DEFINES += QCPDIALOG_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
