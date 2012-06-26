#pragma once
#include "ack/traits/check_inheritance.h"
#include "ack/guarded/guarded_object.h"
#include "ack/guarded/traits.h"

namespace ack {

template <class ImplClas, bool>
class ImplementationCreator;

template <class T>
class GuardWrapper
  : public T
  , public traits::CheckInheritance<T, GuardedObject>
  , public traits::MustHaveVirtualDestructor<T>
{
  friend class ImplementationCreator<T, true>;
protected:
  GuardWrapper()
  {
    GuardedObject::guard().addGuard();
  }
  template <class T1>
  GuardWrapper(const T1& a1)
    : T( a1 )
  {
    GuardedObject::guard().addGuard();
  }
  template <class T1, class T2>
  GuardWrapper(const T1& a1, const T2& a2)
    : T( a1, a2 )
  {
    GuardedObject::guard().addGuard();
  }
  template <class T1, class T2, class T3>
  GuardWrapper(const T1& a1, const T2& a2, const T3& a3)
    : T( a1, a2, a3 )
  {
    GuardedObject::guard().addGuard();
  }
  template <class T1, class T2, class T3, class T4>
  GuardWrapper(const T1& a1, const T2& a2, const T3& a3, const T4& a4)
    : T( a1, a2, a3, a4 )
  {
    GuardedObject::guard().addGuard();
  }
  template <class T1, class T2, class T3, class T4, class T5>
  GuardWrapper(const T1& a1, const T2& a2, const T3& a3, const T4& a4, const T5& a5)
    : T( a1, a2, a3, a4, a5 )
  {
    GuardedObject::guard().addGuard();
  }
  template <class T1, class T2, class T3, class T4, class T5, class T6>
  GuardWrapper(const T1& a1, const T2& a2, const T3& a3, const T4& a4, const T5& a5, const T6& a6)
    : T( a1, a2, a3, a4, a5, a6 )
  {
    GuardedObject::guard().addGuard();
  }
  void safeDelete()
  {
    GuardedObject::guard().pendingDelete();
    if (GuardedObject::guard().counter().waitFor()) // We not in invoke phase can delete...
      delete this;
  }
protected:
  virtual ~GuardWrapper()
  {
    GuardedObject::guard().releaseGuard();
  }
  void WARNING_this_object_MUST_be_created_with_GuardedFactory()
  {}
};

} // namespace ack
