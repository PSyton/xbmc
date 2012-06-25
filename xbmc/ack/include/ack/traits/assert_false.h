#pragma once
#include <boost/type_traits/is_same.hpp>

namespace upal
{
  template <typename T>
  class assert_false
  {
    struct Dummy
    {
    };
  public:
    enum { value = boost::is_same<T,Dummy>::value }; 
  };
}
