#pragma once

namespace ack {
namespace detail {

template <class ImplClass>
struct SimpleCreateStrategy
{
  static ImplClass* create()
  {
    return new ImplClass();
  }
  template <class T1>
  static ImplClass* create( const T1& a1 )
  {
    return new ImplClass( a1 );
  }
  template <class T1, class T2>
  static ImplClass* create( const T1& a1, const T2& a2 )
  {
    return new ImplClass( a1, a2 );
  }
  template <class T1, class T2, class T3>
  static ImplClass* create( const T1& a1, const T2& a2, const T3& a3 )
  {
    return new ImplClass( a1, a2, a3 );
  }
  template <class T1, class T2, class T3, class T4>
  static ImplClass* create( const T1& a1, const T2& a2, const T3& a3, const T4& a4 )
  {
    return new ImplClass( a1, a2, a3, a4 );
  }
  template <class T1, class T2, class T3, class T4, class T5>
  static ImplClass* create( const T1& a1, const T2& a2, const T3& a3, const T4& a4, const T5& a5 )
  {
    return new ImplClass( a1, a2, a3, a4, a5 );
  }
  template <class T1, class T2, class T3, class T4, class T5, class T6>
  static ImplClass* create( const T1& a1, const T2& a2, const T3& a3, const T4& a4, const T5& a5, const T6& a6 )
  {
    return new ImplClass( a1, a2, a3, a4, a5, a6 );
  }
};

} // namespace detail 
} // namespace ack
