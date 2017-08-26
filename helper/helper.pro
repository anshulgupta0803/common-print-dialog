TARGET = cpd-helper
SOURCES += cpd_helper.c
unix {
    target.path = /usr/local/bin
    INSTALLS += target
    CONFIG += link_pkgconfig
    PKGCONFIG += CPDFrontend
}
