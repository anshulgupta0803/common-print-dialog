#ifndef CPD_GLOBAL_H
#define CPD_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CPD_LIBRARY)
#  define CPDSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CPDSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // COMMONPRINTDIALOGLIBRARY_GLOBAL_H
