#pragma once
#include <ack/core/atomic_int.h>
#include <boost/checked_delete.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/static_assert.hpp>

namespace ack {
namespace detail {

struct DefaultDeleteStrategy {};
struct GuardedDeleteStrategy {};

template <class T, class Strategy>
struct Destroyer
{
  static void destroy(T*)
  {
    BOOST_STATIC_ASSERT( !boost::false_type::value );
  }
};

template <class T>
struct Destroyer<T, DefaultDeleteStrategy>
{
  static void destroy(T* objPtr)
  {
    boost::checked_delete( objPtr );
  }
};

template <class T>
struct Destroyer<T, GuardedDeleteStrategy>
{
  static void destroy(T* objPtr)
  {
    objPtr->safeDelete();
  }
};

template <class X>
class BasePtrData
{
private:
  typedef BasePtrData<X> this_type;
  core::AtomicInt m_refCount;
  X* m_ptr;
  BasePtrData(const BasePtrData&); 
  BasePtrData& operator=(const BasePtrData&); 
public:
  BasePtrData( const X* p, int cnt = 0 )
    : m_refCount(cnt)
    , m_ptr((X*)p)
  {
  }
  virtual int addRef()
  {
    if(long(m_refCount) <= 0)
      return 0;

    return m_refCount.add(1);
  }
  virtual int releaseRef()
  {
    if(long(m_refCount) <= 0)
      return 0;
    long ret = m_refCount.sub(1);
    if (ret == 0)
    {
      dispose();
      delete this;
    }

    return ret;
  }

  virtual ~BasePtrData()
  {
    m_refCount = 0;
    m_ptr = 0;
  }
  X& operator* ()
  {
    Q_ASSERT( m_ptr == 0 );
    return *m_ptr;
  }
  const X& operator* () const
  {
    Q_ASSERT( m_ptr == 0 );
    return *m_ptr;
  }
  X* ptr()
  {
    return m_ptr;
  }
  const X* ptr() const
  {
    return m_ptr;
  }
  typedef X* this_type::*unspecified_bool_type;
  operator unspecified_bool_type() const // never throws
  {
    return ( (m_ptr == 0 ) || (int(m_refCount) == 0) ) ? 0 : &this_type::m_ptr;
  }
  virtual void dispose() = 0;
};

//! Класс "сторож" объектов хранимых в указателе.
/** Обеспечивает контроль за временем жизни объекта, указатель на который хранится в "умном указателе"
* \param T - типа хранимого объекта
*/
template <class T, class DelStrat = DefaultDeleteStrategy>
class PtrData
  : public BasePtrData<T>
{
private:
  // Объект не может копироваться ни при каких условиях.
  PtrData(const PtrData&); 
  PtrData& operator=(const PtrData&); 
public:
  //! Контруктор создающий "пустой" объект.
  PtrData()
    : BasePtrData<T>( 0, 1 )
  {}
  //! Контруктор создающий объект с заданным значением уазателя.
  PtrData(const T* p)
    : BasePtrData<T>( p, 1 )
  {}
  virtual ~PtrData()
  {
  }
  virtual void dispose()
  {
    Destroyer<T, DelStrat>:: destroy( BasePtrData<T>::ptr() );
  }
};

} // namespace detail
} // namespace ack