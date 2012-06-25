/*
 * Copyright (C) 2012, PSyton <psytonx@gmail.com>.
 *
 * See the LICENSE file for terms of use.
 */
#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H
#include "global.h"
#include "base_application.h"

namespace ack {
namespace core {

/** Application class.

  Provide main control object for create and run application.

  \param CoreClass
 */

template <class CoreClass>
class Application
        : public BaseApplication
{
public:
    Application(int argc, char *argv[])
        : BaseApplication(argc, argv)
    {
    }
};

} // namespace core
} // namespace ack

#endif // APPLICATION_H
