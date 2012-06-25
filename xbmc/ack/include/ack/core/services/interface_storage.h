#pragma once
#include "ack/core/core_global.h"
#include <boost/unordered/unordered_map.hpp>
#include <boost/uuid/uuid.hpp>

namespace ack {
namespace core {

class ACK_CORE_API InterfaceStorage
{
  typedef boost::unordered_map<boost::uuids::uuid, void*> Interfaces;
  Interfaces m_interfaces;
public:
  virtual void registerInterface(const boost::uuids::uuid& interfaceUuid, void* interfacePtr);
  virtual void* getInterface(const boost::uuids::uuid& interfaceUuid);
};

} // namespace core
} // namespace ack
