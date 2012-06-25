#pragma once


namespace upal
{

  template <int v>
  struct int_val
  {
    operator int() const
    {
      return v;
    }
  };

}//namespace upal
