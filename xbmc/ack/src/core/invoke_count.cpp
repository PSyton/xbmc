#include "ack/core/invoke_count.h"
#include "ack/core/lazy_wait.h"
#include "ack/creators.h"

namespace ack {
namespace core {

InvokeCount::InvokeCount()
  : m_guard( creator(0) )
{
}


void InvokeCount::enter()
{
  m_guard->ref();
}


void InvokeCount::leave()
{
  m_guard->deref();
}


//! Enter if it possible.
/* Returns false if it's possible to enter now.
*/
// Начать критическую секцию если это возможно, (возвращает false если счётчик увеличен, true если это невозможно)
bool InvokeCount::failEnter()
{
  return !m_guard->testAndSet(0, 1);
}


//! Check
bool InvokeCount::isLocked()
{
  return !m_guard->testAndSet(0, 0);
}

void InvokeCount::waitFor()
{
  if ( !lazy_wait( bind_method( &InvokeCount::isLocked, this ) ) )
  {
    // log about it here...
    assert(0);
  }
}


} // namespace core
} // namespace ack
