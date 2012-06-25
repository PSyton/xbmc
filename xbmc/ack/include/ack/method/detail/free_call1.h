#pragma once
#include "function_pointers.h"

namespace ack {
namespace detail {

template<class ObjectType
  , typename A1
  , typename R
  , typename FunctionPointer> 
  inline R free_call( const function_pointers& a_pointers, void* a_ptr, A1 a1 )
{
  return ( static_cast<ObjectType*>(a_ptr)->*reinterpret_cast<FunctionPointer>(a_pointers.funcPtr) )
    (a1);
}

template<class ObjectType
  , typename A1
  , typename R
  , typename FunctionPointer> 
  inline R free_call_multi( const function_pointers& a_pointers, void* a_ptr, A1 a1 )
{
  return ( static_cast<ObjectType*>(a_ptr)->*reinterpret_cast<FunctionPointer>(a_pointers.multiInheritenseFuncPtr) )
    (a1);
}

template<typename A1
  , typename R
  , typename FunctionPointer> 
  inline R free_call_free( const function_pointers& a_pointers, void* , A1 a1 )
{
  return ( *reinterpret_cast<FunctionPointer>(a_pointers.freeFuncPtr) )
    (a1);
}

} // namespace detail
} // namespace ack 
