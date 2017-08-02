QT += qml quick widgets quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

TARGET = cpd
TEMPLATE = lib

CONFIG += c++11 no_keywords
unix {
    target.path = /usr/lib
    INSTALLS += target
    CONFIG += link_pkgconfig
    PKGCONFIG += CPDFrontend gio-unix-2.0 glib-2.0 gobject-2.0 poppler-qt5
}

SOURCES += \
    app/components.cpp \
    app/QCPDialog.cpp \
    cpd.cpp

HEADERS += \
    app/components.h \
    app/QCPDialog.h \
    cpd.h \
    cpd_global.h

RESOURCES += qml.qrc
DEFINES += CPD_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS

QMAKE_LFLAGS += -fPIC
