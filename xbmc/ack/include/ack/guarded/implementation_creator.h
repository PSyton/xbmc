#pragma once
#include "guarded_wrapper.h"

template <class ImplClass, bool createGuarded>
class ImplementationCreator
{
public:
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

template<class ImplClass>
class ImplementationCreator<ImplClass, true>
{
public:
  static ImplClass* create()
  {
    ImplClass* instance = static_cast<ImplClass*>( new GuardWrapper<ImplClass>() );
    static_cast<GuardedObject*>(instance)->onInitiatedAndGuarded();
    return instance;
  }
  template <class T1>
  static ImplClass* create( const T1& a1 )
  {
    ImplClass* instance = static_cast<ImplClass*>( new GuardWrapper<ImplClass>( a1 ) );
    static_cast<GuardedObject*>(instance)->onInitiatedAndGuarded();
    return instance;
  }
  template <class T1, class T2>
  static ImplClass* create( const T1& a1, const T2& a2 )
  {
    ImplClass* instance = static_cast<ImplClass*>( new GuardWrapper<ImplClass>( a1, a2 ) );
    static_cast<GuardedObject*>(instance)->onInitiatedAndGuarded();
    return instance;
  }
  template <class T1, class T2, class T3>
  static ImplClass* create( const T1& a1, const T2& a2, const T3& a3 )
  {
    ImplClass* instance = static_cast<ImplClass*>( new GuardWrapper<ImplClass>( a1, a2, a3 ) );
    static_cast<GuardedObject*>(instance)->onInitiatedAndGuarded();
    return instance;
  }
  template <class T1, class T2, class T3, class T4>
  static ImplClass* create( const T1& a1, const T2& a2, const T3& a3, const T4& a4 )
  {
    ImplClass* instance = static_cast<ImplClass*>( new GuardWrapper<ImplClass>( a1, a2, a3, a4 ) );
    static_cast<GuardedObject*>(instance)->onInitiatedAndGuarded();
    return instance;
  }
  template <class T1, class T2, class T3, class T4, class T5>
  static ImplClass* create( const T1& a1, const T2& a2, const T3& a3, const T4& a4, const T5& a5 )
  {
    ImplClass* instance = static_cast<ImplClass*>( new GuardWrapper<ImplClass>( a1, a2, a3, a4, a5 ) );
    static_cast<GuardedObject*>(instance)->onInitiatedAndGuarded();
    return instance;
  }
  template <class T1, class T2, class T3, class T4, class T5, class T6>
  static ImplClass* create( const T1& a1, const T2& a2, const T3& a3, const T4& a4, const T5& a5, const T6& a6 )
  {
    ImplClass* instance = static_cast<ImplClass*>( new GuardWrapper<ImplClass>( a1, a2, a3, a4, a5, a6 ) );
    static_cast<GuardedObject*>(instance)->onInitiatedAndGuarded();
    return instance;
  }
};

