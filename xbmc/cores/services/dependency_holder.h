#pragma once
#include "abstract_service.h"
#include <boost/uuid/uuid.hpp>
#include <set>


namespace services {

/*! class for hold dependant seriveces uuids.
 */
class DependencesHolder
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

} // namespace services 
