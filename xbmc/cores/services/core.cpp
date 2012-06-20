#include "core.h"
#include "core_ptr.h"

namespace services
{

Core::Core()
{
  CorePtr::m_core = this;
}

Core::~Core()
{
  CorePtr::m_core = 0;
}

bool Core::isValid() const
{
  return true;
}

} // namespace services