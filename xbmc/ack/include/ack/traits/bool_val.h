#pragma once


namespace upal
{

  template <bool v>
  struct bool_val
  {
    operator bool() const
    {
      return v;
    }
  };

}//namespace upal
