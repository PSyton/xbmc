#pragma once

namespace ack {
namespace detail {

//! Check cast one type to another
template<typename From, typename To>
struct could_cast
{
  static From _m_from;
  static To _m_to;
  //! Result
  enum { value = sizeof(_m_from) == sizeof(_m_to) };
};

} // namespace detail
} // namespace ack
