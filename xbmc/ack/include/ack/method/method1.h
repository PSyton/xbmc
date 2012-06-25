#pragma once
#include "detail/method_predeclaration.h"
#include "detail/select_temp_function_pointer.h"
#include "detail/free_call1_function_pointer.h"
#include "detail/method_data.h"

namespace ack {

//! Methods with 1 agument
template<typename A1, typename R> 
class method<R (A1)>
{
  typedef R ReturnType;
  typedef method<ReturnType (A1) >   this_type;
  typedef ReturnType (*FreeCallImplPointer)(const detail::function_pointers&, void*, A1);

  detail::method_data   data;
  FreeCallImplPointer   freeCallImplPtr;

public:
  method()
  {}

  method(const detail::TempFreeFuncPtr& a_func, const FreeCallImplPointer& a_freeFunc)
    : data(a_func)
    , freeCallImplPtr(a_freeFunc)
  {}

  method(const detail::TempFuncPtr& a_func, void* a_ptr, const FreeCallImplPointer& a_freeFunc)
    : data(a_func, a_ptr)
    , freeCallImplPtr(a_freeFunc)
  {}

  method(const detail::TempMultiInheritenseFuncPtr& a_func, void* a_ptr, const FreeCallImplPointer& a_freeFunc)
    : data(a_func, a_ptr)
    , freeCallImplPtr(a_freeFunc)
  {}

  ReturnType operator()(void* ptr, A1 a1) const
  {
    return freeCallImplPtr(data.pointers, ptr, a1);
  }

  ReturnType operator()(A1 a1) const
  {
    return freeCallImplPtr(data.pointers, data.objPtr, a1);
  }

  bool operator ==(const this_type& other) const
  {
    return  (data == other.data)
      &&    (freeCallImplPtr == other.freeCallImplPtr)
      ;
  }

  bool operator !=(const this_type& other) const
  {
    return !operator==(other);
  }

  typedef void* detail::method_data::*unspecified_bool_type;
  operator unspecified_bool_type() const // never throws
  {
    return data;
  }
};


template<class ObjectType, typename R, typename A1> 
inline method<R (A1)> bind_method( R (ObjectType::*a_func)(A1), ObjectType* a_ptr = 0)
{
  typedef R (ObjectType::*FunctionPointer)(A1);
  typedef typename detail::select_temp_function_pointer<FunctionPointer>::type TempFuncPtr;

  return method<R (A1)>(
    reinterpret_cast<TempFuncPtr>(a_func)
    , static_cast<void*>(a_ptr)
    , detail::free_call1_function_pointer<ObjectType, A1, R, FunctionPointer, TempFuncPtr>::get()
    );
}

template<class ObjectType, typename R, typename A1> 
inline method<R (A1)> bind_method( R (ObjectType::* a_func)(A1) const, ObjectType* a_ptr = 0)
{
  typedef R (ObjectType::*FunctionPointer)(A1) const;
  typedef typename detail::select_temp_function_pointer<FunctionPointer>::type TempFuncPtr;

  return method<R (A1)>(
    reinterpret_cast<TempFuncPtr>(a_func)
    , static_cast<void*>(a_ptr)
    , detail::free_call1_function_pointer<ObjectType, A1, R, FunctionPointer, TempFuncPtr>::get()
    );
}

template<typename A1, typename R> 
inline method<R (A1)> bind_method( R (* a_func)(A1))
{
  typedef R (*FunctionPointer)(A1);
  typedef typename detail::TempFreeFuncPtr TempFuncPtr;

  return method<R (A1)>(
    reinterpret_cast<TempFuncPtr>(a_func)
    , detail::free_call1_function_pointer<void, A1, R, FunctionPointer, TempFuncPtr>::get()
    );
}

} // namespace ack
