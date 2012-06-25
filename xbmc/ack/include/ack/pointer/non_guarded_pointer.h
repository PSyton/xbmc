#pragma once
#include "detail/pointer_creator.h"
#include "detail/simple_create_strategy.h"
#include "base_pointer.h"
#include "ack/creators.h"


namespace ack {

template <class T
, class DelStrat = detail::DefaultDeleteStrategy
, template <class, template <class> class CreateStrategy> class InitializerStrategy = detail::PointerCreator >
class NonGuardedPointer
  : public BasePointer<T, T, DelStrat, detail::SimpleCreateStrategy<T> >
  , public InitializerStrategy<NonGuardedPointer<T, DelStrat, InitializerStrategy>, detail::SimpleCreateStrategy>
{
  typedef BasePointer<T, T, DelStrat, detail::SimpleCreateStrategy<T> >  Parent;
  typedef NonGuardedPointer<T, DelStrat, InitializerStrategy>         this_type;

public:
  NonGuardedPointer()
  {}

  explicit NonGuardedPointer(const T* ptr)
    : Parent( ptr )
  {}

  NonGuardedPointer(const detail::Creator0& obj)
    : Parent( obj )
  {}

  template<typename T0>
  NonGuardedPointer(const detail::Creator1<T0>& obj)
    : Parent( obj )
  {}

  template<typename T0, typename T1>
  NonGuardedPointer(const detail::Creator2<T0, T1>& obj)
    : Parent( obj )
  {}

  template<typename T0, typename T1, typename T2>
  NonGuardedPointer(const detail::Creator3<T0, T1, T2>& obj)
    : Parent( obj )
  {}

  template<typename T0, typename T1, typename T2, typename T3>
  NonGuardedPointer(const detail::Creator4<T0, T1, T2, T3>& obj)
    : Parent( obj )
  {}
  
  NonGuardedPointer& operator=(const this_type& other)
  {
    this_type(other).swap(*this);
    return *this;
  }

  NonGuardedPointer& operator=(int ptr)
  {
    (void)ptr;
    assert(ptr == 0);
    this_type().swap(*this);
    return *this;
  }

  void assign(const T* ptr)
  {
    this_type(ptr).swap(*this);
  }
};

} //namespace ack
