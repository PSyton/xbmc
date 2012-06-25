#pragma once

namespace ack {
namespace detail {

template<typename PointerType, template <class> class CreateStrategy>
struct PointerCreator
{
  template<typename Type>
  struct create_strategy
  {
    typedef CreateStrategy<Type> type;
  };

  static PointerType init()  
  {
    return PointerType( CreateStrategy<typename PointerType::type>::create( ) );
  }

  template <class T1>
  static PointerType init(const T1& t1) 
  {
    return PointerType( CreateStrategy<typename PointerType::type>::create( t1 ) );
  }

  template <class T1, class T2>
  static PointerType init(const T1& t1, const T2&  t2) 
  {
    return PointerType( CreateStrategy<typename PointerType::type>::create( t1, t2 ) );
  }

  template <class T1, class T2, class T3>
  static PointerType init(const T1& t1, const T2&  t2, const T3&  t3) 
  {
    return PointerType( CreateStrategy<typename PointerType::type>::create( t1, t2, t3 ) );
  }

  template <class T1, class T2, class T3, class T4>
  static PointerType init(const T1& t1, const T2&  t2, const T3&  t3, const T4&  t4) 
  {
    return PointerType( CreateStrategy<typename PointerType::type>::create( t1, t2, t3, t4 ) );
  }

  template <class T1, class T2, class T3, class T4, class T5>
  static PointerType init(const T1& t1, const T2&  t2, const T3&  t3, const T4&  t4, const T5&  t5) 
  {
    return PointerType( CreateStrategy<typename PointerType::type>::create( t1, t2, t3, t4, t5 ) );
  }
};

} // namespace detail
} // namespace ack
