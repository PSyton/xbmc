#pragma once


namespace upal {

  template <class Enum, Enum Value>
  class enum_val
  {
  public:
    operator Enum() const
    {
      return Value;
    }
  };

}//namespace upal
