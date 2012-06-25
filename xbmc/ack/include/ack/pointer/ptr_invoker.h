#pragma once
#include <assert.h>

namespace ack {

template <class Ptr>
class PtrInvoker
{
  Ptr* m_ptr;
  typedef PtrInvoker<Ptr> ThisClass;
protected:
  void set(Ptr* val)
  {
    m_ptr = val;
  }
public:
  PtrInvoker(Ptr* p = 0)
    : m_ptr(p)
  {
  }

  virtual ~PtrInvoker()
  {
    m_ptr = 0;
  }

  Ptr* get() const
  {
    assert(0 != m_ptr);
    return m_ptr;
  }

  Ptr* pointer() const
  {
    return get();
  }

  Ptr* operator->() const
  {
    return get();
  }

  typedef Ptr* ThisClass::*unspecified_bool_type;
  operator unspecified_bool_type() const // never throws
  {
    return m_ptr == 0 ? 0 : &ThisClass::m_ptr;
  }

  bool isNull() const
  {
    return ( 0 == m_ptr );
  }

  bool isValid() const
  {
    return ( 0 != m_ptr );
  }

  template <typename FType>
  void safeCall(const FType& method)
  {
    if ( isValid() )
      (get()->*method)();
  }
  template <typename FType, typename Arg1>
  void safeCall(const FType& method, Arg1& a1)
  {
    if ( isValid() )
      (get()->*method)(a1);
  }
  template <typename FType, typename Arg1, typename Arg2>
  void safeCall(const FType& method, Arg1& a1, Arg2& a2)
  {
    if ( isValid() )
      (get()->*method)(a1, a2);
  }
  template <typename FType, typename Arg1, typename Arg2, typename Arg3>
  void safeCall(const FType& method, Arg1& a1, Arg2& a2, Arg3& a3)
  {
    if ( isValid() )
      (get()->*method)(a1, a2, a3);
  }
  template <typename FType, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
  void safeCall(const FType& method, Arg1& a1, Arg2& a2, Arg3& a3, Arg4& a4)
  {
    if ( isValid() )
      (get()->*method)(a1, a2, a3, a4);
  }

  //////////////////////////////////////////////////////////////////////////
  // const param versions 
  template <typename FType, typename Arg1>
  void safeCall(const FType& method, const Arg1& a1)
  {
    if ( isValid() )
      (get()->*method)(a1);
  }
  template <typename FType, typename Arg1, typename Arg2>
  void safeCall(const FType& method, const Arg1& a1, const Arg2& a2)
  {
    if ( isValid() )
      (get()->*method)(a1, a2);
  }
  template <typename FType, typename Arg1, typename Arg2, typename Arg3>
  void safeCall(const FType& method, const Arg1& a1, const Arg2& a2, const Arg3& a3)
  {
    if ( isValid() )
      (get()->*method)(a1, a2, a3);
  }
  template <typename FType, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
  void safeCall(const FType& method, const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4)
  {
    if ( isValid() )
      (get()->*method)(a1, a2, a3, a4);
  }
};

} // namespace ack
