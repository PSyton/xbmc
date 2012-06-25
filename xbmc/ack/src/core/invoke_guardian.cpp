#include "ack/core/invoke_guardian.h"
#include "ack/core/invoke_count.h"


namespace ack {
namespace core {

InvokeGuardian::InvokeGuardian(InvokeCount* a_counter)
  : m_counter(a_counter)
{
  counter()->enter();
}

InvokeGuardian::~InvokeGuardian()
{
  counter()->leave();
}

} // namespace core
} // namespace ack
