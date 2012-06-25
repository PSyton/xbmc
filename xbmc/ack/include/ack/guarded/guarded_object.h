#pragma once
#include "detail/guard_object.h"

namespace ack {

class GuardedObject
{
  detail::GuardObject m_guard;
protected:
  GuardedObject() {}
  virtual ~GuardedObject() {}
  virtual void WARNING_this_object_MUST_be_created_with_GuardedFactory() = 0;
public:
  detail::GuardObject guard() const
  {
    return m_guard;
  }
  //! Called by creation factory when object construction has finished.
  virtual void onInitiatedAndGuarded()
  {
  }
};

} // namespace ack
