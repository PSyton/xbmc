#pragma once

namespace boost {
namespace uuids {
class uuid;
}
}

namespace services {

typedef std::list<boost::uuids::uuid> UuidsList;

class AbstractService;

class AbstractServiceFactory
{
public:
  virtual AbstractService* create(const boost::uuids::uuid& aUuid) = 0;
  virtual void destroy(AbstractService* servicePtr) = 0;
  UuidList uuidsList() const = 0;
  bool canCreate(const boost::uuids::uuid& aUuid) const = 0;
  virtual ~AbstractServiceFactory() {}
};

} // namespace services

