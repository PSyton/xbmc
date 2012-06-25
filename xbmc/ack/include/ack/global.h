#pragma once
#include "ack_config.h"
#ifdef USE_QT
#include <QtCore/qglobal.h>
#endif

#ifndef USE_QT
#if defined(_WIN32) || defined(_WIN64)
#define ACK_OS_WIN
#endif
#  if defined(ACK_OS_WIN)
#    define EXPORT_API __declspec(dllexport)
#    define IMPORT_API __declspec(dllimport)
#  endif
#  ifndef EXPORT_API
#    define EXPORT_API
#  endif
#  ifndef IMPORT_API
#    define IMPORT_API
#  endif
#else
#  define EXPORT_API Q_DECL_EXPORT
#  define IMPORT_API Q_DECL_IMPORT
#endif

namespace ack {

} // namespace ack
