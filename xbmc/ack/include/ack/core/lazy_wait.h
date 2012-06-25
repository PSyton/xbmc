#pragma once
#include "ack/core/core_global.h"
#include "ack/method/method0.h"

namespace ack {
namespace core {

typedef ack::method<bool ()>   WaitCondition;

//! Stop current thread while condition is true.
/**
  \param condition [in] Functor for checking condition
  \param msecsInterval [in] Sleep interval between condition checks in msec
  \param timeout [in] Maximum time for waiting. For infinite wait set it to 0. Default value - 30000 msec
  \return false if stop waiting on timeout.
 */
ACK_CORE_API bool lazy_wait(const WaitCondition& condition
                           , unsigned long msecsInterval = 1
                           , unsigned long timeout = 30000);

} // namespace core
} // namespace ack
