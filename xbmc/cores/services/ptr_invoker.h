#pragma once
#include <assert.h>

namespace services {

template <class PointerType>
class PtrInvoker
{
  PointerType* m_ptr;
  typedef PtrInvoker<PointerType> ThisClass;
public:
  PtrInvoker(PointerType* ptr)
    : m_ptr(ptr)
  {
  }
  ~PtrInvoker()
  {
    m_ptr = 0;
  }
  PointerType* get()
  {
    assert(0 != m_ptr);
    return m_ptr;
  }
  PointerType* operator->()
  {
    return get();
  }
  const PointerType* operator->() const
  {
    return static_cast<ThisClass*>(this)->get();
  }
  typedef PointerType* ThisClass::*unspecified_bool_type;
  operator unspecified_bool_type() const // never throws
  {
    return m_ptr == 0 ? 0 : &ThisClass::m_ptr;
  }
  bool isNull() const
  {
    return (0 == m_ptr);
  }
  bool operator==(int ptr) const
  {
    (void)ptr; // prevent unused varrning in release
    assert(ptr == 0);
    return isNull();
  }
};

} // namespace services
