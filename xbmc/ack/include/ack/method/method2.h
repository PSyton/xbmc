#pragma once
#include "detail/method_predeclaration.h"
#include "detail/select_temp_function_pointer.h"
#include "detail/free_call2_function_pointer.h"
#include "detail/method_data.h"


namespace ack {

//! Methods with 2 arguments
template<typename A1, typename A2, typename R> 
class method<R (A1, A2)>
{
  typedef R ReturnType;
  typedef method<ReturnType (A1, A2) >   this_type;
  typedef ReturnType (*FreeCallImplPointer)(const detail::function_pointers&, void*, A1, A2);

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

  ReturnType operator()(void* ptr, A1 a1, A2 a2) const
  {
    return freeCallImplPtr(data.pointers, ptr, a1, a2);
  }

  ReturnType operator()(A1 a1, A2 a2) const
  {
    return freeCallImplPtr(data.pointers, data.objPtr, a1, a2);
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


template<class ObjectType, typename A1, typename A2, typename R> 
inline method<R (A1, A2)> bind_method( R (ObjectType::* a_func)(A1, A2), ObjectType* a_ptr = 0)
{
  typedef R (ObjectType::*FunctionPointer)(A1, A2);
  typedef typename detail::select_temp_function_pointer<FunctionPointer>::type TempFuncPtr;

  return method<R (A1, A2)>(
    reinterpret_cast<TempFuncPtr>(a_func)
    , static_cast<void*>(a_ptr)
    , detail::free_call2_function_pointer<ObjectType, A1, A2, R, FunctionPointer, TempFuncPtr>::get()
    );
}

template<class ObjectType, typename A1, typename A2, typename R> 
inline method<R (A1, A2)> bind_method( R (ObjectType::* a_func)(A1, A2) const, ObjectType* a_ptr = 0)
{
  typedef R (ObjectType::*FunctionPointer)(A1, A2) const;
  typedef typename detail::select_temp_function_pointer<FunctionPointer>::type TempFuncPtr;

  return method<R (A1, A2)>(
    reinterpret_cast<TempFuncPtr>(a_func)
    , static_cast<void*>(a_ptr)
    , detail::free_call2_function_pointer<ObjectType, A1, A2, R, FunctionPointer, TempFuncPtr>::get()
    );
}

template<typename A1, typename A2, typename R> 
inline method<R (A1, A2)> bind_method( R (* a_func)(A1, A2))
{
  typedef R (*FunctionPointer)(A1, A2);
  typedef typename detail::TempFreeFuncPtr TempFuncPtr;

  return method<R (A1, A2)>(
    reinterpret_cast<TempFuncPtr>(a_func)
    , detail::free_call2_function_pointer<void, A1, A2, R, FunctionPointer, TempFuncPtr>::get()
    );
}

}//namespace ack
