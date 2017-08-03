#ifndef QCPDIALOG_GLOBAL_H
#define QCPDIALOG_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QCPDIALOG_LIBRARY)
#  define CPDSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CPDSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QCPDIALOG_GLOBAL_H
