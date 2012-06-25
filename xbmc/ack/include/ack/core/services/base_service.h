#pragma once
#include "abstract_service.h"
#include "dependences_holder.h"
#include "interface_storage.h"
#include "service_ptr.h"
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_base_of.hpp>

namespace ack {
namespace core {

template <class RootInterfaceClass>
class BaseService
  : public RootInterfaceClass
{
  InterfaceStorage m_storage;
  bool m_initialized;
  DependencesHolder m_dependences;
protected:
  virtual InterfaceStorage& storage()
  {
    return m_storage;
  }
  virtual void shutdown()
  {
    // First finish dependant services...
/*    while (m_dependences.size())
    {
      ServicePtr<AbstractService> ptr(m_dependences.pop());
      if (ptr)
        ptr->shutdown();
    }
*/
    onShutdown();
  }
public:
  BaseService()
    : m_initialized(false)
  {
    BOOST_STATIC_ASSERT( (boost::is_base_of<AbstractService, RootInterfaceClass>::value) );
    storage().registerInterface(RootInterfaceClass::rootUuid(), static_cast<void*>(this));
  }
  virtual const boost::uuids::uuid& uuid() const
  {
    return RootInterfaceClass::rootUuid();
  }
  virtual bool init()
  {
    return true;
  }
  virtual bool resolveDependances()
  {
    // Base implementation has no dependences...
    return true;
  }
  virtual bool addDependent(const boost::uuids::uuid& depUuid)
  {
    m_dependences.addUuid(depUuid);
    return checkDependencesTree();
  }
  virtual void removeDependent(const boost::uuids::uuid& depUuid)
  {
    m_dependences.removeUuid(depUuid);
  }
  virtual bool checkDependencesTree()
  {
    return m_dependences.checkDependences();
  }
  virtual bool dependsOf(const boost::uuids::uuid& depUuid)
  {
    ServicePtr<AbstractService> ptr(depUuid);
    if (ptr)
      return ptr->addDependent(this->uuid());
    return false;
  }
  virtual void onInit()
  {
  }
  virtual void onShutdown()
  {
  }
  virtual bool isInitialized() const
  {
    return m_initialized;
  }
  virtual void setInitilizationStatus(bool status)
  {
    m_initialized = status;
  }
};

} // namespace core
} // namespace ack
