#pragma once
#include "temp_function_pointer_types.h"


namespace ack {
namespace detail {

//! Set of pointers to functions
union function_pointers
{
  //! Method of class with multiple inheritance
  TempMultiInheritenseFuncPtr   multiInheritenseFuncPtr;
  //! Pointer to member
  TempFuncPtr                   funcPtr;
  //! Pointer to free function
  TempFreeFuncPtr               freeFuncPtr;


  //! Default constructor
  inline function_pointers()
    : multiInheritenseFuncPtr(0)
  {}

  //! Constructor from member
  inline function_pointers(const TempFuncPtr& a_funcPtr)
    : funcPtr(a_funcPtr)
  {}

  //! Constructor from member of class with multiple inheritance
  inline function_pointers(const TempMultiInheritenseFuncPtr& a_multiInheritenseFuncPtr)
    : multiInheritenseFuncPtr(a_multiInheritenseFuncPtr)
  {}

  //! Constructor from free function
  inline function_pointers(const TempFreeFuncPtr& a_freeFuncPtr)
    : freeFuncPtr(a_freeFuncPtr)
  {}

  inline bool operator ==(const function_pointers& other) const
  {
    return  (multiInheritenseFuncPtr == other.multiInheritenseFuncPtr)
      ;
  }
};

} // namespace detail
} // namespace ack