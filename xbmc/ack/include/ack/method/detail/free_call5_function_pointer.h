#pragma once
#include "temp_function_pointer_types.h"
#include "free_call5.h"


namespace ack {
namespace detail {

template<class ObjectType
  , typename A1
  , typename A2
  , typename A3
  , typename A4
  , typename A5
  , typename R
  , typename FunctionPointer
  , typename TempFunctionPointer
>
struct free_call5_function_pointer
{
};

template<class ObjectType
  , typename A1
  , typename A2
  , typename A3
  , typename A4
  , typename A5
  , typename R
  , typename FunctionPointer>
struct free_call5_function_pointer<ObjectType, A1, A2, A3, A4, A5, R, FunctionPointer, TempFuncPtr>
{
  typedef R (*FreeCallImplPointer)(const function_pointers&, void*, A1, A2, A3, A4, A5);

  static inline FreeCallImplPointer get()
  {
    return &detail::free_call<ObjectType, A1, A2, A3, A4, A5, R, FunctionPointer>;
  }
};

template<class ObjectType
  , typename A1
  , typename A2
  , typename A3
  , typename A4
  , typename A5
  , typename R
  , typename FunctionPointer>
struct free_call5_function_pointer<ObjectType, A1, A2, A3, A4, A5, R, FunctionPointer, TempMultiInheritenseFuncPtr>
{
  typedef R (*FreeCallImplPointer)(const function_pointers&, void*, A1, A2, A3, A4, A5);

  static inline FreeCallImplPointer get()
  {
    return &detail::free_call_multi<ObjectType, A1, A2, A3, A4, A5, R, FunctionPointer>;
  }
};

template<typename A1
  , typename A2
  , typename A3
  , typename A4
  , typename A5
  , typename R
  , typename FunctionPointer>
struct free_call5_function_pointer<void, A1, A2, A3, A4, A5, R, FunctionPointer, TempFreeFuncPtr>
{
  typedef R (*FreeCallImplPointer)(const detail::function_pointers&, void*, A1, A2, A3, A4, A5);

  static inline FreeCallImplPointer get()
  {
    return &detail::free_call_free<A1, A2, A3, A4, A5, R, FunctionPointer>;
  }
};

}//namespace detail
}//namespace ack
