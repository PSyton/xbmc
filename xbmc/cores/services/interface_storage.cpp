#include "interface_storage.h"
#include <assert.h>


namespace services {

void InterfaceStorage::registerInterface(const boost::uuids::uuid& interfaceUuid, void* interfacePtr)
{
  assert(!interfaceUuid.is_nil());
  assert(0 != interfacePtr);
  Interfaces::iterator it = m_interfaces.find(interfaceUuid);
  if (it == m_interfaces.end())
    m_interfaces.insert(std::make_pair(interfaceUuid, interfacePtr));
}

void* InterfaceStorage::getInterface(const boost::uuids::uuid& interfaceUuid)
{
  Interfaces::const_iterator it = m_interfaces.find(interfaceUuid);
  if (it == m_interfaces.end())
    return 0;
  return it->second;
}


} // namespace services
