#include "ack/for_each_type.h"
#include <unittest++/UnitTest++.h>
#include <boost/mpl/list.hpp>

struct X
{
  enum {value = 1};
};

typedef boost::mpl::list<X, X, X, X, X> TList;

struct FunctorT
{
  int count;
  FunctorT()
    : count(0)
  {
  }

  template<class Type>
  void operator()()
  {
    count += Type::value;
  }
};


TEST(ForeachTypeTest)
{
  FunctorT f;
  ack::algorithm::for_each_type<TList>(f);
  CHECK_EQUAL(f.count, 5);
}