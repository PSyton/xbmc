#pragma once
#include "reference_support.h"


namespace upal
{

  template <typename Key, typename Value, typename DefValue = Value, typename ReferenceSupport = const_reference_support>
  struct key_value
  {
    typedef Key                     key_type;
    typedef Value                   value_type;
    typedef DefValue                def_value_type;
    typedef ReferenceSupport        reference_support_type;

    typedef key_type                first_type;    
    typedef value_type              second_type;    
    typedef def_value_type          third_type;    
    typedef reference_support_type  fourth_type;    
  };

}//namespace upal
