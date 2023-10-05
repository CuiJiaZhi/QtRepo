#ifndef QTPLOT_GLOBAL_H
#define QTPLOT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QTPLOT_LIBRARY)
#  define QTPLOT_EXPORT Q_DECL_EXPORT
#else
#  define QTPLOT_EXPORT Q_DECL_IMPORT
#endif

#endif // QTPLOT_GLOBAL_H
