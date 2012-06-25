#include "ack/core/core.h"
#include "ack/core/core_ptr.h"

namespace ack {
namespace core {

Core::Core()
  : m_initialized(false)
  , m_shutdown(false)
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

void Core::initialize()
{

  m_initialized = true;
}

AbstractService* Core::getService(const boost::uuids::uuid& sUuid)
{
  return 0;
}

void Core::shutdown()
{
  m_shutdown = true;
  // \todo stop services here.
}

bool Core::isTerminating() const
{
  return m_shutdown;
}

bool Core::isInitialized() const
{
  return m_initialized;
}


} // namespace core
} // namespace ack
