#pragma once

namespace boost {
namespace uuids {
class uuid;
}
}

namespace services {

class AbstractService;

class Core {

public:
  Core();
  virtual ~Core();
  virtual bool isValid() const;
  
  AbstractService* getService(const boost::uuids::uuid& sUuid);
};

} // namespace services
