#pragma once

namespace ack {
namespace detail {

//! Select type by flag value
template<bool flag, typename Type1, typename Type2>
struct select_type
{
};

template<typename Type1, typename Type2>
struct select_type<true, Type1, Type2>
{
  typedef Type1 type;
};

template<typename Type1, typename Type2>
struct select_type<false, Type1, Type2>
{
  typedef Type2 type;
};

} // namespace detail
} // namespace ack
