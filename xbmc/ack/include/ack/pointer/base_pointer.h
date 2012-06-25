#pragma once
#include "detail/ptr_data.h"
#include "ack/creators.h"
#include <assert.h>

namespace ack {
/*! \file
    \ingroup pointer
*/  

//! Base implementation for smart pointers
template <class CreatedType
  , class HoldedType
  , class delete_strategy
  , class create_strategy >
class BasePointer
{
  typedef BasePointer<CreatedType, HoldedType, delete_strategy, create_strategy>  this_type;

protected:
  typedef typename detail::BasePtrData<HoldedType> BasePtrData;
  BasePtrData* m_data;

public:
  typedef HoldedType   type;
  typedef HoldedType*  ptr_type;
  typedef detail::PtrData<HoldedType, delete_strategy> PtrData;


  ~BasePointer()
  {
    if ( m_data )
    {
      m_data->releaseRef();
      m_data = 0;
    }
  }

  BasePointer()
    : m_data( 0 )
  {}

  explicit BasePointer(const HoldedType* ptr)
    : m_data( new PtrData( (HoldedType*)ptr) )
  {}

  BasePointer(const this_type& other)
    : m_data( other.m_data )
  {
    if ( m_data )
      m_data->addRef();
  }

  BasePointer(const detail::Creator0&)
    : m_data( new PtrData(create_strategy::create()) )
  {
  }

  template<typename T0>
  BasePointer(const detail::Creator1<T0>& obj)
    : m_data( new PtrData(create_strategy::create(obj.arg0)) )
  {
  }

  template<typename T0, typename T1>
  BasePointer(const detail::Creator2<T0, T1>& obj)
    : m_data( new PtrData(create_strategy::create(obj.arg0, obj.arg1)) )
  {
  }

  template<typename T0, typename T1, typename T2>
  BasePointer(const detail::Creator3<T0, T1, T2>& obj)
    : m_data( new PtrData(create_strategy::create(obj.arg0, obj.arg1, obj.arg2)) )
  {
  }

  template<typename T0, typename T1, typename T2, typename T3>
  BasePointer(const detail::Creator4<T0, T1, T2, T3>& obj)
    : m_data( new PtrData(create_strategy::create(obj.arg0, obj.arg1, obj.arg2, obj.arg3)) )
  {
  }

  //! Added to support for boost::mem_fn 
  HoldedType* get() const
  {
    assert(m_data);
    return m_data->ptr();
  }

  const HoldedType* operator->() const
  {
    return m_data->ptr();
  }

  HoldedType* operator->() 
  {
    return get();
  }

  const HoldedType& operator*() const
  {
    const HoldedType* ret = get();
    assert(ret);
    return *ret;
  }

  HoldedType& operator*()
  {
    HoldedType* ret = get();
    assert(ret);
    return *ret;
  }

  void swap(this_type& other)
  {
    BasePtrData* temp = m_data;
    m_data = other.m_data;
    other.m_data = temp;
  }

  void reset()
  {
    this_type().swap(*this);
  }

  bool operator ==(const this_type& other) const
  {
    return ( m_data == other.m_data );
  }

  bool operator !=(const this_type &other) const
  {
    return ( m_data != other.m_data );
  }

  typedef BasePtrData* this_type::*unspecified_bool_type;
  operator unspecified_bool_type() const // never throws
  {
    return ( m_data == 0 || !*m_data ) ? 0 : &this_type::m_data;
  }
};

}//namespace ack
