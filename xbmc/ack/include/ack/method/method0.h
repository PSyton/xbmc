#pragma once
#include "detail/method_predeclaration.h"
#include "detail/select_temp_function_pointer.h"
#include "detail/free_call0_function_pointer.h"
#include "detail/method_data.h"

namespace ack {

//! Methods without arguments
template<typename R>
class method<R (void)>
{  
  typedef R ReturnType;
  typedef method<ReturnType ()>   this_type;
  typedef ReturnType (*FreeCallImplPointer)(const detail::function_pointers&, void*);

  //! Base dataset
  detail::method_data   data;
  //! Pointer to free function which meke casted function call
  FreeCallImplPointer   freeCallImplPtr;

public:
  //! Create empty method
  method()
  {}

  //! Create form pointer to fre function
  method(const detail::TempFreeFuncPtr& a_func, const FreeCallImplPointer& a_freeFunc)
    : data(a_func)
    , freeCallImplPtr(a_freeFunc)
  {}

  //! Create from pointer to method and object's pointer
  method(const detail::TempFuncPtr& a_func, void* a_ptr, const FreeCallImplPointer& a_freeFunc)
    : data(a_func, a_ptr)
    , freeCallImplPtr(a_freeFunc)
  {}

  //! Create from pointer to const method and object's pointer
  method(const detail::TempMultiInheritenseFuncPtr& a_func, void* a_ptr, const FreeCallImplPointer& a_freeFunc)
    : data(a_func, a_ptr)
    , freeCallImplPtr(a_freeFunc)
  {}

  //! Call
  inline ReturnType operator()(void* ptr) const
  {
    return freeCallImplPtr(data.pointers, ptr);
  }

  //! Call
  inline ReturnType operator()() const
  {
    return freeCallImplPtr(data.pointers, data.objPtr);
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


//////////////////////////////////////////////////////////////////////////
// Bind and creating objects

template<class ObjectType, typename R> 
inline method<R ()> bind_method( R (ObjectType::* a_func)(), ObjectType* a_ptr = 0)
{
  typedef R (ObjectType::*FunctionPointer)();
  typedef typename detail::select_temp_function_pointer<FunctionPointer>::type TempFuncPtr;

  return method<R ()>(
    reinterpret_cast<TempFuncPtr>(a_func)
    , static_cast<void*>(a_ptr)
    , detail::free_call0_function_pointer<ObjectType, R, FunctionPointer, TempFuncPtr>::get()
    );
}
  
template<class ObjectType, typename R> 
inline method<R ()> bind_method( R (ObjectType::* a_func)() const, ObjectType* a_ptr = 0)
{
  typedef R (ObjectType::*FunctionPointer)() const;
  typedef typename detail::select_temp_function_pointer<FunctionPointer>::type TempFuncPtr;

  return method<R ()>(
    reinterpret_cast<TempFuncPtr>(a_func)
    , static_cast<void*>(a_ptr)
    , detail::free_call0_function_pointer<ObjectType, R, FunctionPointer, TempFuncPtr>::get()
    );
}

template<typename R> 
inline method<R ()> bind_method( R (* a_func)())
{
  typedef R (*FunctionPointer)();
  typedef typename detail::TempFreeFuncPtr TempFuncPtr;

  return method<R ()>(
    reinterpret_cast<TempFuncPtr>(a_func)
    , detail::free_call0_function_pointer<void, R, FunctionPointer, TempFuncPtr>::get()
    );
}

} // namespace ack
