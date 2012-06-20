#pragma once
#include <boost/unordered/unordered_map.hpp>
#include <boost/uuid/uuid.hpp>

namespace services {

class InterfaceStorage
{
  typedef boost::unordered_map<boost::uuids::uuid, void*> Interfaces;
  Interfaces m_interfaces;
public:
  virtual void registerInterface(const boost::uuids::uuid& interfaceUuid, void* interfacePtr);
  virtual void* getInterface(const boost::uuids::uuid& interfaceUuid);
};

} // namespace services