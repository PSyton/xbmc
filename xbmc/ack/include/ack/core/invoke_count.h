#pragma once
#include "ack/core/core_global.h"
#include "ack/pointer/non_guarded_pointer.h"
#include <ack/core/atomic_int.h>

namespace ack {
namespace core {

// Class for prevent destroy Guarded object while it's callbacks invoked.
class ACK_CORE_API InvokeCount
{
  typedef NonGuardedPointer<AtomicInt> GuardPtr;
  GuardPtr m_guard;
  bool failEnter();
public:
  InvokeCount();
  //! Invoke begin
  void enter();
  //! Invoke finished
  void leave();
  bool isLocked();
  bool waitFor();
};

} // namespace core
} // namespace ack
