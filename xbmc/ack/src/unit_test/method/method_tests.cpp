#include "ack/method/method0.h"
#include "ack/method/method1.h"
#include "ack/method/method2.h"
#include "ack/method/method3.h"
#include "ack/method/method4.h"
#include "ack/method/method5.h"
#include <unittest++/UnitTest++.h>
#include <string>


// Free functions bind and call
static bool f_0 = false;
void free_v0()
{
  f_0 = true;
}

static bool f_1 = false;
void free_v1(bool v)
{
  f_1 = v;
}

#define TEST_V2 100
void free_v2(int x, bool& b)
{
  b = x == TEST_V2;
}

static bool f_3 = false;
#define TEST_V3 std::string("text")
#define TEST_V4 2.44
void free_v3(const std::string& str, int x, double y)
{
  f_3 = (TEST_V3 == str
         && x == TEST_V2
         && y == TEST_V4);
}

static bool f_4 = false;
void free_v4(const std::string& str, int x, double y, bool b)
{
  f_4 = (TEST_V3 == str
    && x == TEST_V2
    && y == TEST_V4
    && b);
}

TEST(TestFreeVoidFunctions)
{
  ack::method<void ()> m0 = ack::bind_method(&free_v0);
  m0();
  CHECK(f_0);

  ack::method<void (bool)> m1 = ack::bind_method(&free_v1);
  m1(true);
  CHECK(f_1);

  ack::method<void (int, bool&)> m2 = ack::bind_method(&free_v2);
  bool bv = false;
  m2(TEST_V2, bv);
  CHECK(bv);

  ack::method<void (const std::string&, int, double)> m3 = ack::bind_method(&free_v3);
  m3(TEST_V3, TEST_V2, TEST_V4);
  CHECK(f_3);

  ack::method<void (const std::string&, int, double, bool)> m4 = ack::bind_method(&free_v4);
  m4(TEST_V3, TEST_V2, TEST_V4, true);
  CHECK(f_4);
}

bool free_0()
{
  return true;
}

int free_1(int x)
{
  return x;
}

int free_2(int x, int x1)
{
  return x + x1;
}

int free_3(int x, int x1, int x2)
{
  return x + x1 + x2;
}

int free_4(int x, int x1, int x2, int x3)
{
  return x + x1 + x2 + x3;
}

int free_5(int x, int x1, int x2, int x3, int x4)
{
  return x + x1 + x2 + x3 + x4;
}

TEST(TestFreeFunctions)
{
  ack::method<bool ()> m0 = ack::bind_method(&free_0);
  CHECK(m0());

  ack::method<int (int)> m1 = ack::bind_method(&free_1);
  CHECK_EQUAL(m1(TEST_V2), TEST_V2);

  ack::method<int (int, int)> m2 = ack::bind_method(&free_2);
  CHECK_EQUAL(m2(TEST_V2, TEST_V2), TEST_V2 + TEST_V2);

  ack::method<int (int, int, int)> m3 = ack::bind_method(&free_3);
  CHECK_EQUAL(m3(TEST_V2, TEST_V2, TEST_V2), TEST_V2 + TEST_V2 + TEST_V2);

  ack::method<int (int, int, int, int)> m4 = ack::bind_method(&free_4);
  CHECK_EQUAL(m4(TEST_V2, TEST_V2, TEST_V2, TEST_V2), TEST_V2 + TEST_V2 + TEST_V2 + TEST_V2);

  ack::method<int (int, int, int, int, int)> m5 = ack::bind_method(&free_5);
  CHECK_EQUAL(m5(TEST_V2, TEST_V2, TEST_V2, TEST_V2, TEST_V2), TEST_V2 + TEST_V2 + TEST_V2 + TEST_V2 + TEST_V2);
}

class BaseTestClass1
{
public:
  bool called;
  BaseTestClass1()
    : called(false)
  {
  }
  void void_0()
  {
    called = bool_0();
  }
  void void_1(int x)
  {
    called = bool_1(x);
  }
  void void_2(int x, bool b)
  {
    called = bool_2(x, b);
  }
  void void_3(int x, double y, bool b)
  {
    called = bool_3(x, y, b);
  }
  void void_4(int x, double y, bool b, const std::string& s)
  {
    called = bool_4(x, y, b, s);
  }
  void void_5(int x, double y, bool b, const std::string& s, int z)
  {
    called = bool_5(x, y, b, s, z);;
  }
  bool bool_0() const
  {
    return true;
  }
  bool bool_1(int x) const
  {
    return x == TEST_V2;
  }
  bool bool_2(int x, bool b) const
  {
    return (x == TEST_V2 && b);
  }
  bool bool_3(int x, double y, bool b) const
  {
    return (x == TEST_V2 && b && y == TEST_V4);
  }
  bool bool_4(int x, double y, bool b, const std::string& s) const
  {
    return (x == TEST_V2 && b && y == TEST_V4 && s == TEST_V3);;
  }
  bool bool_5(int x, double y, bool b, const std::string& s, int z) const
  {
    return (x == TEST_V2 && b && y == TEST_V4 && s == TEST_V3 && z == x);
  }
};

TEST(TestSimpleMethods)
{
  BaseTestClass1 c[12];
  int count = 0;
  // 0 arguments
  ack::method<void (void)> m0 = ack::bind_method(&BaseTestClass1::void_0, &(c[count]));
  m0();
  CHECK(c[count++].called);

  ack::method<bool (void)> mb0 = ack::bind_method(&BaseTestClass1::bool_0, &(c[count++]));
  CHECK(mb0());

  // 1 arguments
  ack::method<void (int)> m1 = ack::bind_method(&BaseTestClass1::void_1, &(c[count]));
  m1(TEST_V2);
  CHECK(c[count++].called);

  ack::method<bool (int)> mb1 = ack::bind_method(&BaseTestClass1::bool_1, &(c[count++]));
  CHECK(mb1(TEST_V2));

  // 2 arguments
  ack::method<void (int, bool)> m2 = ack::bind_method(&BaseTestClass1::void_2, &(c[count]));
  m2(TEST_V2, true);
  CHECK(c[count++].called);

  ack::method<bool (int, bool)> mb2 = ack::bind_method(&BaseTestClass1::bool_2, &(c[count++]));
  CHECK(mb2(TEST_V2, true));

  // 3 arguments
  ack::method<void (int, double, bool)> m3 = ack::bind_method(&BaseTestClass1::void_3, &(c[count]));
  m3(TEST_V2, TEST_V4, true);
  CHECK(c[count++].called);

  ack::method<bool (int, double, bool)> mb3 = ack::bind_method(&BaseTestClass1::bool_3, &(c[count++]));
  CHECK(mb3(TEST_V2 ,TEST_V4, true));

  // 4 arguments
  ack::method<void (int, double, bool, const std::string&)> m4 = ack::bind_method(&BaseTestClass1::void_4, &(c[count]));
  m4(TEST_V2, TEST_V4, true, TEST_V3);
  CHECK(c[count++].called);

  ack::method<bool (int, double, bool, const std::string&)> mb4 = ack::bind_method(&BaseTestClass1::bool_4, &(c[count++]));
  CHECK(mb4(TEST_V2 ,TEST_V4, true, TEST_V3));

  // 5 arguments
  ack::method<void (int, double, bool, const std::string&, int)> m5 = ack::bind_method(&BaseTestClass1::void_5, &(c[count]));
  m5(TEST_V2, TEST_V4, true, TEST_V3, TEST_V2);
  CHECK(c[count++].called);

  ack::method<bool (int, double, bool, const std::string&, int)> mb5 = ack::bind_method(&BaseTestClass1::bool_5, &(c[count++]));
  CHECK(mb5(TEST_V2, TEST_V4, true, TEST_V3, TEST_V2));
}

struct Parent1
{
  virtual bool virtualConst() const
  {
    return false;
  }
  virtual ~Parent1(){}
};

struct Parent2
{
  bool nonVirtual() const
  {
    return true;
  }
  virtual ~Parent2(){}
};

struct Parent3
{
};

struct X
  : public Parent1
  , public Parent2
  , public Parent3
{
  virtual bool virtualConst() const
  {
    return true;
  }
  bool nonVirtual() const
  {
    return false;
  }
};

TEST(TestValidations)
{
  Parent1 p1;
  ack::method<bool ()> m1;
  CHECK(!m1);
  m1 = ack::bind_method(&Parent1::virtualConst, &p1);
  CHECK(m1);
}

TEST(TestInheitance)
{
  Parent1 p1;
  ack::method<bool ()> m1 = ack::bind_method(&Parent1::virtualConst, &p1);
  CHECK(!m1());

  X x1;
  // Check call of virtual method
  CHECK( ack::bind_method(&Parent1::virtualConst, (Parent1*)&x1)() );
  CHECK( ack::bind_method(&X::virtualConst, &x1)() );

  // Check overrides
  CHECK( ack::bind_method(&Parent2::nonVirtual, (Parent2*)&x1)() );
  CHECK( !ack::bind_method(&X::nonVirtual, &x1)() );
}
