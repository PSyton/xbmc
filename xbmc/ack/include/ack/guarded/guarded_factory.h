#pragma once
#include "implementation_creator.h"
#include "guarded_object.h"

namespace ack {

template <class Class>
class GuardedFactory
{
  typedef ImplementationCreator<Class, boost::is_base_of<GuardedObject, Class>::value> CreatorType;

public:
  static Class* create()
  {
    return CreatorType::create();
  }
  template <class T1>
  static Class* create(const T1& a1)
  {
    return CreatorType::create( a1 );
  }
  template <class T1, class T2>
  static Class* create(const T1& a1, const T2& a2)
  {
    return CreatorType::create( a1, a2 );
  }
  template <class T1, class T2, class T3>
  static Class* create(const T1& a1, const T2& a2, const T3& a3)
  {
    return CreatorType::create( a1, a2, a3 );
  }
  template <class T1, class T2, class T3, class T4>
  static Class* create(const T1& a1, const T2& a2, const T3& a3, const T4& a4)
  {
    return CreatorType::create( a1, a2, a3, a4 );
  }
  template <class T1, class T2, class T3, class T4, class T5>
  static Class* create(const T1& a1, const T2& a2, const T3& a3, const T4& a4, const T4& a5)
  {
    return CreatorType::create( a1, a2, a3, a4, a5 );
  }
  template <class T1, class T2, class T3, class T4, class T5, class T6>
  static Class* create(const T1& a1, const T2& a2, const T3& a3, const T4& a4, const T5& a5, const T6& a6)
  {
    return CreatorType::create( a1, a2, a3, a4, a5, a6 );
  }
};

} // namespace ack

