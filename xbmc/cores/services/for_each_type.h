#pragma once
#include <boost/mpl/deref.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/end.hpp>

namespace detail {
namespace algorithm {

template <class Begin, class End>
class for_each_type_internal
{
  typedef typename boost::mpl::deref<Begin>::type type;
  typedef typename boost::mpl::next<Begin>::type Next;

public:
  template<typename Functor>
  static void exec(Functor& functor)
  {
    functor.template operator()<type>();
    for_each_type_internal<Next, End>::exec(functor);
  }
};

template <class End>
class for_each_type_internal<End, End>
{
public:
  template<typename Functor>
  static void exec(Functor&)
  {
  }
};

} //namespace algorithm  
} //namespace details

namespace algorithm {

template<typename TypeList, typename Functor>
void for_each_type(Functor& functor)
{
  typedef typename ::detail::upal::algorithm::for_each_type_internal<typename boost::mpl::begin<TypeList>::type,
  typename boost::mpl::end<TypeList>::type > internal_implemetation;

  internal_implemetation::exec(functor);
}

} //namespace algorithm
