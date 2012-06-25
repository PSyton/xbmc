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

  //! ��������������� �� ��������� �� ������� � ��������� �� ������
  inline method_data(const TempFreeFuncPtr& a_func)
    : pointers(a_func)
    , objPtr(reinterpret_cast<void*>(1))
  {}

  //! ��������������� �� ��������� �� ������� � ��������� �� ������
  inline method_data(const TempFuncPtr& a_func, void* a_ptr)
    : pointers(a_func)
    , objPtr(a_ptr)
  {}

  //! ��������������� �� ��������� �� ������� � ������������� ������������� � ��������� �� ������
  inline method_data(const TempMultiInheritenseFuncPtr& a_func, void* a_ptr)
    : pointers(a_func)
    , objPtr(a_ptr)
  {}

  //! �������� �������� ���� ���������
  inline bool operator ==(const method_data& other) const
  {
    return  (pointers == other.pointers)
      &&    (objPtr == other.objPtr)
      ;
  }

  typedef void* method_data::*unspecified_bool_type;
  //! �������� ���������
  inline operator unspecified_bool_type() const // never throws
  {
    return ( 0 != objPtr ) ? &method_data::objPtr : 0;
  }
};

} // namespace detail
} // namespace ack
