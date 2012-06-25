#pragma once
#include "free_call0.h"

namespace ack {
namespace detail {

//! Declaration of call-function
template<class ObjectType
  , typename R
  , typename FunctionPointer
  , typename TempFunctionPointer
>
struct free_call0_function_pointer
{
};

//! Generate pointer to method
template<class ObjectType
  , typename R
  , typename FunctionPointer>
struct free_call0_function_pointer<ObjectType, R, FunctionPointer, TempFuncPtr>
{
  typedef R (*FreeCallImplPointer)(const detail::function_pointers&, void*);

  static inline FreeCallImplPointer get()
  {
    return &detail::free_call<ObjectType, R, FunctionPointer>;
  }
};

//! Generate pointer to method of class with multiple inheritance
template<class ObjectType
  , typename R
  , typename FunctionPointer>
struct free_call0_function_pointer<ObjectType, R, FunctionPointer, TempMultiInheritenseFuncPtr>
{
  typedef R (*FreeCallImplPointer)(const detail::function_pointers&, void*);

  static inline FreeCallImplPointer get()
  {
    return &detail::free_call_multi<ObjectType, R, FunctionPointer>;
  }
};

//! Generate pointer to free function
template<typename R
  , typename FunctionPointer>
struct free_call0_function_pointer<void, R, FunctionPointer, TempFreeFuncPtr>
{
  typedef R (*FreeCallImplPointer)(const detail::function_pointers&, void*);

  static inline FreeCallImplPointer get()
  {
    return &detail::free_call_free<R, FunctionPointer>;
  }
};

} // namespace detail
} // namespace ack
