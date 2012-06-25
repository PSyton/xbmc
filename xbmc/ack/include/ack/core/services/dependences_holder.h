#pragma once
#include "ack/core/core_global.h"
#include "ack/core/services/abstract_service.h"
#include <boost/uuid/uuid.hpp>
#include <set>


namespace ack {
namespace core {

/*! class for hold dependant seriveces uuids.
 */
class ACK_CORE_API DependencesHolder
{
private:
  typedef std::set<boost::uuids::uuid> Uuids;
  Uuids m_uuids;
  bool m_resolving;

  Uuids& uuids();
public:
  DependencesHolder();
  void addUuid(const boost::uuids::uuid& depUuid);
  void removeUuid(const boost::uuids::uuid& depUuid);
  boost::uuids::uuid pop();
  size_t size() const;
  bool checkDependences();
};

} // namespace core
} // namespace ack
