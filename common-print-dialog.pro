QT += qml quick widgets quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

TARGET = cpd
TEMPLATE = lib

CONFIG += c++11 no_keywords
unix {
    target.path = /usr/lib
    INSTALLS += target
    CONFIG += link_pkgconfig
    PKGCONFIG += gio-unix-2.0 glib-2.0 gobject-2.0 poppler-qt5
}

SOURCES += \
    cpd.cpp \
    app/components.cpp \
    app/window.cpp

RESOURCES += qml.qrc

LIBS += -lcups

DEPENDPATH += backends/cups
INCLUDEPATH += $${DEPENDPATH}

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS COMMONPRINTDIALOGLIBRARY_LIBRARY

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    cpd.h \
    cpd_global.h \
    app/components.h \
    app/window.h

LIBS +=  -L/usr/lib/ -lCPDFrontend

INCLUDEPATH += $$PWD/backends/cups/release/headers
DEPENDPATH += $$PWD/backends/cups/release/headers
