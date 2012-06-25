#pragma once
#include "function_pointers.h"


namespace ack {
namespace detail {

template<class ObjectType
  , typename A1
  , typename A2
  , typename A3
  , typename A4
  , typename R
  , typename FunctionPointer> 
  inline R free_call( const function_pointers& a_pointers, void* a_ptr, A1 a1, A2 a2, A3 a3, A4 a4 )
{
  return ( static_cast<ObjectType*>(a_ptr)->*reinterpret_cast<FunctionPointer>(a_pointers.funcPtr) )
    (a1, a2, a3, a4);
}

template<class ObjectType
  , typename A1
  , typename A2
  , typename A3
  , typename A4
  , typename R
  , typename FunctionPointer> 
  inline R free_call_multi( const function_pointers& a_pointers, void* a_ptr, A1 a1, A2 a2, A3 a3, A4 a4 )
{
  return ( static_cast<ObjectType*>(a_ptr)->*reinterpret_cast<FunctionPointer>(a_pointers.multiInheritenseFuncPtr) )
    (a1, a2, a3, a4);
}

template<typename A1
  , typename A2
  , typename A3
  , typename A4
  , typename R
  , typename FunctionPointer> 
  inline R free_call_free( const function_pointers& a_pointers, void* , A1 a1, A2 a2, A3 a3, A4 a4 )
{
  return ( *reinterpret_cast<FunctionPointer>(a_pointers.freeFuncPtr) )
    (a1, a2, a3, a4);
}

}//namespace detail
}//namespace ack
