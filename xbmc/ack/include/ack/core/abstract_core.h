#pragma once

namespace boost {
namespace uuids {
  struct uuid;
}
}

namespace ack {
namespace core {

class AbstractService;

class AbstractCore
{
public:
  virtual bool isValid() const = 0;
  virtual AbstractService* getService(const boost::uuids::uuid& sUuid) = 0;
  virtual void shutdown() = 0;
  virtual bool isInitialized() const = 0;
  virtual bool isTerminating() const = 0;
  virtual ~AbstractCore() {}
};

} // namespace core
} // namespace ack
