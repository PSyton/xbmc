#pragma once
#include "temp_simple_class.h"
#include "temp_multi_inheritense_class.h"

namespace ack {
namespace detail {

typedef void (temp_simple::*TempFuncPtr)();
typedef void (temp_multi_inheritense::*TempMultiInheritenseFuncPtr)();
typedef void (*TempFreeFuncPtr)();

} // namespace detail
} // namespace ack
