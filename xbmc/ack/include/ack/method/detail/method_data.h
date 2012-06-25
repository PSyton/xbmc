#pragma once
#include "function_pointers.h"
#include "temp_function_pointer_types.h"


namespace ack {
namespace detail {

//! Base method data
struct method_data
{  
  function_pointers pointers;
  //! Pointer to object
  void* objPtr;

  //! Empty data
  inline method_data()
    : objPtr(0)
  {}

  //! Конструирование по указателю на функцию и указатель на объект
  inline method_data(const TempFreeFuncPtr& a_func)
    : pointers(a_func)
    , objPtr(reinterpret_cast<void*>(1))
  {}

  //! Конструирование по указателю на функцию и указатель на объект
  inline method_data(const TempFuncPtr& a_func, void* a_ptr)
    : pointers(a_func)
    , objPtr(a_ptr)
  {}

  //! Конструирование по указателю на функцию с множественным наследованием и указатель на объект
  inline method_data(const TempMultiInheritenseFuncPtr& a_func, void* a_ptr)
    : pointers(a_func)
    , objPtr(a_ptr)
  {}

  //! Оператор равества себе подобному
  inline bool operator ==(const method_data& other) const
  {
    return  (pointers == other.pointers)
      &&    (objPtr == other.objPtr)
      ;
  }

  typedef void* method_data::*unspecified_bool_type;
  //! Операция валидации
  inline operator unspecified_bool_type() const // never throws
  {
    return ( 0 != objPtr ) ? &method_data::objPtr : 0;
  }
};

} // namespace detail
} // namespace ack
