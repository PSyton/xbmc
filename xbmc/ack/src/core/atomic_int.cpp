#include "ack/core/atomic_int.h"
#include "threads/Atomics.h"

namespace ack {
namespace core {

AtomicInt::AtomicInt(long val /*= 0*/)
  : m_value(val)
{
}

bool AtomicInt::ref()
{
  return AtomicIncrement(&m_value) != 0;
}

bool AtomicInt::deref()
{
  return AtomicDecrement(&m_value) != 0;
}

bool AtomicInt::testAndSet(long expectedValue, long newValue)
{
  return cas(&m_value, expectedValue, newValue) == expectedValue;
}

bool AtomicInt::operator==(long val) const
{
  return m_value == val;
}

bool AtomicInt::operator!=(long val) const
{
  return m_value != val;
}

bool AtomicInt::operator!() const
{
  return m_value == 0;
}

AtomicInt::operator long() const
{
  return m_value;
}

AtomicInt& AtomicInt::operator=(long val)
{
  m_value = val;
  return *this;
}

long AtomicInt::add(long valueToAdd)
{
  return AtomicAdd(&m_value, valueToAdd);
}

long AtomicInt::sub(long valueToSub)
{
  return AtomicSubtract(&m_value, valueToSub);
}

long AtomicInt::fetchAndStore(long newValue)
{
  long old_val;
  do {
    old_val = m_value;
  } while (cas(&m_value, old_val, newValue) != old_val);
  return old_val;
}


} // namespace core
} // namespace ack

