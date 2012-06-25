#pragma once
#include "ack/core/core_global.h"

namespace ack {
namespace core {

class ACK_CORE_API AtomicInt
{
  volatile long m_value;

public:
  // non atomic
  inline AtomicInt(long val = 0);
  bool operator==(long val) const;
  bool operator!=(long val) const;
  bool operator!() const;
  operator long() const;
  AtomicInt &operator=(long val);
  // atomic
  bool ref();
  bool deref();
  bool testAndSet(long expectedValue, long newValue);
  long add(long valueToAdd);
  long sub(long valueToSub);
};

} // namespace core
} // namespace ack
