/*
 * Copyright (C) 2012, PSyton <psytonx@gmail.com>.
 *
 * See the LICENSE file for terms of use.
 */

#include "ack/core/base_application.h"


namespace ack {
namespace core {

BaseApplication::BaseApplication(int argc, char *argv[])
    : m_argc(argc)
    , m_argv(argv)
{
    static const char *const s_empty = "";
    if (m_argc == 0 || m_argv == 0)
    {
      m_argc = 0;
      m_argv = (char **)&s_empty;
    }
}

int BaseApplication::run()
{
    return 0;
}

BaseApplication::~BaseApplication()
{
}

} // namespace core
} // namespace ack
