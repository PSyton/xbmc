#pragma once
#include "ack/core/invoke_count.h"
#include "ack/pointer/non_guarded_pointer.h"
#include <ack/core/atomic_int.h>

namespace ack {
namespace detail {

#define DESTROYED_STATE 0l
#define CONSTRUCTION_STATE 1l
#define GUARDED_STATE 2l
#define PENDING_DELETE_STATE 3l

class GuardObject
{
  typedef NonGuardedPointer<core::AtomicInt> GuardPtr;
  GuardPtr m_ptr;
  mutable core::InvokeCount m_counter; //!< критическая секция
public:
  GuardObject()
    : m_ptr(creator(CONSTRUCTION_STATE))
  {}
  core::InvokeCount& counter() const
  {
    return m_counter;
  }
  void addGuard()
  {
    bool success = m_ptr->testAndSet(CONSTRUCTION_STATE, GUARDED_STATE);
    assert(success);
  }
  void pendingDelete()
  {
    bool success = m_ptr->testAndSet(GUARDED_STATE, PENDING_DELETE_STATE);
    assert(success);
  }
  void releaseGuard()
  {
    bool success = m_ptr->testAndSet(PENDING_DELETE_STATE, DESTROYED_STATE);
    assert(success);
  }
  bool isGuarded() const
  {
    return (*m_ptr == GUARDED_STATE);
  }
  bool isConstructing() const
  {
    return (*m_ptr == CONSTRUCTION_STATE);
  }
  bool destroyAfterInvoke() const
  {
    return (*m_ptr == PENDING_DELETE_STATE);
  }
  bool isDestroyed() const
  {
    return (*m_ptr == DESTROYED_STATE);
  }
};

} // namespace detail
} // namespace ack
