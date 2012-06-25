#pragma once
#include "guarded_object.h"
#include "ack/traits/dummy.h"
#include <boost/type_traits/has_virtual_destructor.hpp>
#include <boost/mpl/if.hpp>

namespace ack {
namespace traits {

class No_Virtual_Destructor_Found
{
private:
  No_Virtual_Destructor_Found();
};

template <class T>
class MustHaveVirtualDestructor
  : public boost::mpl::if_c< boost::has_virtual_destructor<T>::value, DummyClass<No_Virtual_Destructor_Found>, No_Virtual_Destructor_Found >::type
{
};

} // namespace traits
} // namespace ack