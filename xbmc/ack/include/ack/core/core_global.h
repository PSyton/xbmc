/*
 * Copyright (C) 2012, PSyton <psytonx@gmail.com>.
 *
 * See the LICENSE file for terms of use.
 */
#pragma once
#ifndef CORE_GLOBAL_H
#define CORE_GLOBAL_H

#include "ack/global.h"

#ifdef ACK_CORE_STATIC
    #define ACK_CORE_API
#else
    #ifdef ACK_CORE_LIB
        #define ACK_CORE_API EXPORT_API
    #else
        #define ACK_CORE_API IMPORT_API
    #endif
#endif

#endif // CORE_GLOBAL_H
