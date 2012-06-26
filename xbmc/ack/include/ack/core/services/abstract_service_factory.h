#pragma once
#include <list>

namespace boost {
namespace uuids {
struct uuid;
}
}

namespace ack {
namespace core {

typedef std::list<boost::uuids::uuid> UuidsList;

class AbstractService;

class AbstractServiceFactory
{
public:
  virtual AbstractService* create(const boost::uuids::uuid& aUuid) = 0;
  virtual void destroy(AbstractService* servicePtr) = 0;
  virtual UuidsList uuidsList() const = 0;
  virtual bool canCreate(const boost::uuids::uuid& aUuid) const = 0;
  virtual ~AbstractServiceFactory() {}
};

} // namespace core
} // namespace ack

