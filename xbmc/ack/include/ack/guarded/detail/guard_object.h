#pragma once
#include "ack/core/invoke_count.h"
#include "ack/pointer/non_guarded_pointer.h"
#include <ack/core/atomic_int.h>

namespace ack {
namespace detail {

class GuardObject
{
  typedef NonGuardedPointer<core::AtomicInt> GuardPtr;
  GuardPtr m_ptr;
  mutable core::InvokeCount m_counter; //!< критическая секция
public:
  GuardObject()
    : m_ptr(creator(1))
  {}

  core::InvokeCount& counter() const
  {
    return m_counter;
  }

  void addGuard()
  {
    m_ptr->ref();
  }
  void releaseGuard()
  {
    m_ptr->deref();
  }
  bool isGuarded() const
  {
    return (*m_ptr == 2l);
  }
  bool isConstructing() const
  {
    return (*m_ptr == 1l);
  }
  bool isDestroyed() const
  {
    return (*m_ptr == 0l);
  }
};

} // namespace detail
} // namespace ack
