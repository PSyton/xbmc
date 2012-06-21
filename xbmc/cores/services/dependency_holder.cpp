#include "dependency_holder.h"
#include "service_ptr.h"

namespace services {

DependencesHolder::Uuids& DependencesHolder::uuids()
{
  return m_uuids;
}


DependencesHolder::DependencesHolder()
  : m_resolving(false)
{
}

void DependencesHolder::addUuid(const boost::uuids::uuid& depUuid)
{
  if (uuids().find(depUuid) == uuids().end())
    uuids().insert(depUuid);
}

void DependencesHolder::removeUuid(const boost::uuids::uuid& depUuid)
{
  uuids().erase(depUuid);
}

boost::uuids::uuid DependencesHolder::pop()
{
  if (size() > 0)
  {
    boost::uuids::uuid ret = *(uuids().begin());
    removeUuid(ret);
    return ret;
  }
  return boost::uuids::uuid();
}

size_t DependencesHolder::size() const
{
  return const_cast<DependencesHolder*>(this)->uuids().size();
}

bool DependencesHolder::checkDependences()
{
  // Corcular depenancy
  if (m_resolving)
    return false;
  m_resolving = true;
  bool isOk = true;
    
  Uuids forRemove;
  for (Uuids::iterator it = uuids().begin(); isOk && it != uuids().end(); ++it)
  {
    ServicePtr<AbstractService> ptr(*it);
    if (!ptr)
      forRemove.insert(*it);
    else
    {
      if (!ptr->checkDependancesTree())
        isOk = false;
    }
  }
  // Cleanup
  for (Uuids::iterator it = forRemove.begin(); it != forRemove.end(); ++it)
    uuids().erase(*it);

  m_resolving = false;
  return isOk;
}


} // namespace services 
