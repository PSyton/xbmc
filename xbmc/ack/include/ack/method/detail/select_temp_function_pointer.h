#pragma once
#include "temp_function_pointer_types.h"
#include "could_cast.h"
#include "select_type.h"
#include "could_not_cast.h"


namespace ack {
namespace detail {

//! Get type of pointer to function we can cast
template<class FunctionPointer>
class select_temp_function_pointer
{
  // Check possibility of cast for simple class
  enum { could_cast_to_simple =  could_cast<FunctionPointer, TempFuncPtr>::value };
  // On result select pointer to simple class instance or incorrect value
  typedef typename select_type<could_cast_to_simple
    , TempFuncPtr
    , could_not_cast>::type  result_temp1;

  // Check cast possibility for class with multiple inheritance 
  enum { could_cast_to_multi_inheritense =  could_cast<FunctionPointer, TempMultiInheritenseFuncPtr>::value };
  // If we can't cast - invalid value
  typedef typename select_type<could_cast_to_multi_inheritense
    , TempMultiInheritenseFuncPtr
    , result_temp1>::type  result_type2;

public:
  typedef result_type2 type;
};

} // namespace detail
} // namespace ack
