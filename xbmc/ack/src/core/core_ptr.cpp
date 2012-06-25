#include "ack/core/core_ptr.h"
#include "ack/core/abstract_core.h"
#include <assert.h>

namespace ack {
namespace core {

AbstractCore* CorePtr::m_core = 0;

CorePtr::CorePtr()
  : PtrInvoker<AbstractCore>(m_core)
{
}

bool CorePtr::isValid() const
{
  return (!isNull()
          && m_core->isValid());
}

} // namespace core
} // namespace ack
