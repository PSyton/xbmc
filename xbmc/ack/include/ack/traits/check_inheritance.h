#pragma once
#include "dummy.h"
#include <boost/type_traits/is_base_of.hpp>
#include <boost/mpl/if.hpp>

namespace ack {
namespace traits {

struct dummy {};
template <typename Base>
class Not_Derived_From
{
#ifndef Q_OS_MAC
  Not_Derived_From();
#endif
};

template <typename Derived, typename Base, typename ErrorType>
struct CheckInheritanceWithError
{
  typedef typename boost::mpl::if_c< boost::is_base_of<Base, Derived>::value, dummy, Not_Derived_From<Base> >::type type;
};

template <typename Derived, typename Base>
struct CheckInheritance
{
  CheckInheritance()
  {
    typename CheckInheritanceWithError<Derived, Base, Not_Derived_From<Base> >::type();
  }
};

} // namespace traits
} // namespace ack
