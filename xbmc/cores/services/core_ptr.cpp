#include "core_ptr.h"
#include "core.h"
#include <assert.h>

namespace services {

Core* CorePtr::m_core = 0;

CorePtr::CorePtr()
  : PtrInvoker<Core>(m_core)
{
}

bool CorePtr::isValid() const
{
  return (!isNull()
          && m_core->isValid());
}

} // namespace services
