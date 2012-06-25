#pragma once
/*
 * Copyright (C) 2012, PSyton <psytonx@gmail.com>.
 *
 * See the LICENSE file for terms of use.
 *
 * \author Vadim Fedotov, 2011
 */
namespace ack {
namespace detail {
//! Class "creation flag" without arguments
struct Creator0
{
  Creator0()
  {
  }
};

//! Class "creation flag" with single argument
template<typename T0>
struct Creator1
{
  const T0& arg0;

  Creator1(const T0& a_arg0)
    : arg0(a_arg0)
  {
  }
};

//! Class "creation flag" with 2 arguments
template<typename T0, typename T1>
struct Creator2
{
  const T0& arg0;
  const T1& arg1;

  Creator2(const T0& a_arg0, const T1& a_arg1)
    : arg0(a_arg0)
    , arg1(a_arg1)
  {
  }
};

//! Class "creation flag" with 3 arguments
template<typename T0, typename T1, typename T2>
struct Creator3
{
  const T0& arg0;
  const T1& arg1;
  const T2& arg2;

  Creator3(const T0& a_arg0, const T1& a_arg1, const T2& a_arg2)
    : arg0(a_arg0)
    , arg1(a_arg1)
    , arg2(a_arg2)
  {
  }
};

//! Class "creation flag" with 4 arguments
template<typename T0, typename T1, typename T2, typename T3>
struct Creator4
{
  const T0& arg0;
  const T1& arg1;
  const T2& arg2;
  const T3& arg3;

  Creator4(const T0& a_arg0, const T1& a_arg1, const T2& a_arg2, const T3& a_arg3)
    : arg0(a_arg0)
    , arg1(a_arg1)
    , arg2(a_arg2)
    , arg3(a_arg3)
  {
  }
};

} //namespace detail


inline detail::Creator0 creator()
{
  return detail::Creator0();
}

template<typename T0>
inline detail::Creator1<T0> creator(const T0& a_arg0)
{
  return detail::Creator1<T0>(a_arg0);
}

template<typename T0, typename T1>
inline detail::Creator2<T0, T1> creator(const T0& a_arg0,
                                        const T1& a_arg1)
{
  return detail::Creator2<T0, T1>(a_arg0, a_arg1);
}

template<typename T0, typename T1, typename T2>
inline detail::Creator3<T0, T1, T2> creator(const T0& a_arg0,
                                            const T1& a_arg1,
                                            const T2& a_arg2)
{
  return detail::Creator3<T0, T1, T2>(a_arg0, a_arg1, a_arg2);
}

template<typename T0, typename T1, typename T2, typename T3>
inline detail::Creator4<T0, T1, T2, T3> creator(const T0& a_arg0,
                                                const T1& a_arg1,
                                                const T2& a_arg2,
                                                const T3& a_arg3)
{
  return detail::Creator4<T0, T1, T2, T3>(a_arg0, a_arg1, a_arg2, a_arg3);
}

} //namespace ack
