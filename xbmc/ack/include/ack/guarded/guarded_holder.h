#pragma once
#include "guarded_object.h"

namespace ack {

//! This class holds Guard object and pointer for guarded object.
class GuardedHolder
{
  detail::GuardObject m_guard;
  GuardedObject* m_object;
public:
  GuardedHolder()
    : m_object(0)
  {
  }
  GuardedHolder(GuardedObject* a_guardedObj)
    : m_guard(a_guardedObj->guard())
    , m_object(a_guardedObj)
  {
  }
  bool guarded() const
  {
    bool ret = m_guard.isGuarded();
    if (!ret && isConstructing())
    {
      assert(0);
    }
    return ret;
  }
  //! True means that destructor for wrapper object has called
  bool isDestroyed() const
  {
    return m_guard.isDestroyed();
  }
  //! True means that object in constructing phase
  bool isConstructing() const
  {
    return m_guard.isConstructing();
  }
  bool destroyAfterInvoke() const
  {
    return m_guard.destroyAfterInvoke();
  }
  GuardedObject* object() const
  {
    return m_object;
  }
  const detail::GuardObject& getGuard() const
  {
    return m_guard;
  }
};

} // namespace ack

