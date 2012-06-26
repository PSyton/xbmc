#pragma once
#include "ack/pointer/detail/pointer_creator.h"
#include "ack/pointer/base_pointer.h"
#include "ack/creators.h"
#include "ack/guarded/guarded_factory.h"
#include "ack/method/detail/select_type.h"
#include <boost/type_traits/is_base_of.hpp>

namespace ack {

/*! \file
    \ingroup pointer
*/  

//!
/**
 * <b>Usage:</b>
 * \code
 * class A;
 * 
 * Pointer<A> ptr( new A() );
 * Pointer<A> ptr1 = ptr;
 * \endcode
 */
template <class T
, class DelStrat = typename detail::select_type<boost::is_base_of<GuardedObject, T>::value, detail::GuardedDeleteStrategy, detail::DefaultDeleteStrategy>::type
, template <class, template <class> class CreateStrategy> class InitializerStrategy = detail::PointerCreator >
class Pointer
  : public BasePointer<T, T, DelStrat, GuardedFactory<T> >
  , public InitializerStrategy<Pointer<T, DelStrat, InitializerStrategy>, GuardedFactory>
{
  typedef BasePointer<T, T, DelStrat, GuardedFactory<T> >  Parent;
  typedef Pointer<T, DelStrat, InitializerStrategy>     this_type;

public:
  Pointer()
  {}

  explicit Pointer(const T* ptr)
    : Parent( ptr )
  {}

  // Support for creation via Creator class
  Pointer(const detail::Creator0& obj)
    : Parent( obj )
  {
  }

  template<typename T0>
  Pointer(const detail::Creator1<T0>& obj)
    : Parent( obj )
  {
  }

  template<typename T0, typename T1>
  Pointer(const detail::Creator2<T0, T1>& obj)
    : Parent( obj )
  {
  }

  template<typename T0, typename T1, typename T2>
  Pointer(const detail::Creator3<T0, T1, T2>& obj)
    : Parent( obj )
  {
  }

  template<typename T0, typename T1, typename T2, typename T3>
  Pointer(const detail::Creator4<T0, T1, T2, T3>& obj)
    : Parent( obj )
  {
  }

  void assign(const T* ptr)
  {
    this_type(ptr).swap(*this);
  }

  Pointer& operator=(const this_type& other)
  {
    this_type(other).swap(*this);
    return *this;
  }

  Pointer& operator =(int ptr)
  {
    (void)ptr;
    assert(ptr == 0);
    this_type().swap(*this);
    return *this;
  }
};

} //namespace ack


namespace boost {

//! get_pointer() enables boost::mem_fn to recognize smart pointer
template<class T> inline T* get_pointer(::ack::Pointer<T, typename ::ack::detail::select_type<boost::is_base_of<::ack::GuardedObject, T>::value, ::ack::detail::GuardedDeleteStrategy, ::ack::detail::DefaultDeleteStrategy>::type> const & p)
{
  return p.get();
}

}//namespace boost
