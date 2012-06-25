#pragma once

namespace detail {

template<typename PointerType, template <class> class CreateStrategy>
struct EmptyPointerCreator
{
  template<typename Type>
  struct create_strategy
  {
    typedef CreateStrategy<Type> type;
  };

};

} //namespace detail 
