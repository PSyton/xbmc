#pragma once
#include "function_pointers.h"

namespace ack {
namespace detail {

//! Call method
template<class ObjectType
  , typename R
  , typename FunctionPointer>
  inline R free_call( const function_pointers& a_pointers, void* a_ptr )
{
  return ( static_cast<ObjectType*>(a_ptr)->*reinterpret_cast<FunctionPointer>(a_pointers.funcPtr) )
    ();
}

//! Call method of class with multiple inheritance
template<class ObjectType
  , typename R
  , typename FunctionPointer> 
  inline R free_call_multi( const function_pointers& a_pointers, void* a_ptr )
{
  return ( static_cast<ObjectType*>(a_ptr)->*reinterpret_cast<FunctionPointer>(a_pointers.multiInheritenseFuncPtr) )
    ();
}

//! Call free function
template<typename R
  , typename FunctionPointer> 
  inline R free_call_free( const function_pointers& a_pointers, void*  )
{
  return ( *reinterpret_cast<FunctionPointer>(a_pointers.freeFuncPtr) )
    ();
}

} // namespace detail
} // namespace ack