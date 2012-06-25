/*
 * Copyright (C) 2012, PSyton <psytonx@gmail.com>.
 *
 * See the LICENSE file for terms of use.
 */
#pragma once
#ifndef BASE_APPLICATION_H
#define BASE_APPLICATION_H
#include "core_global.h"


namespace ack {
namespace core {

class ACK_CORE_API BaseApplication
{
private:
    int m_argc;
    char** m_argv;
protected:
    BaseApplication(int argc, char *argv[]);
public:
    virtual int run();
    virtual ~BaseApplication();
};

} // namespace core
} // namespace ack

#endif // BASE_APPLICATION_H
