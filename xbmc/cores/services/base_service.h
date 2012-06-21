#pragma once
#include "abstract_service.h"
#include "interface_storage.h"
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_base_of.hpp>

namespace services {

template <class RootInterfaceClass>
class BaseService
  : public RootInterfaceClass
{
  InterfaceStorage m_storage;
  bool m_initialized;
  DependancyHolder m_dependancyHolder;
protected:
  virtual InterfaceStorage& storage()
  {
    return m_storage;
  }
  virtual void shutdown()
  {
    // First finish dependant services...
    while (m_dependancyHolder.size())
    {
      ServicePtr<AbstractService> ptr(m_dependancyHolder.pop());
      if (ptr)
        ptr->shutdown();
    }
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
    // Base implementation nas no dependences...
    return true;
  }
  virtual bool addDependant(const boost::uuids::uuid& depUuid)
  {
    m_dependancyHolder.addDependant(depUuid)
    return checkDependancesTree();
  }
  virtual void removeDependant(const boost::uuids::uuid& depUuid)
  {
    m_dependancyHolder.removeDependant(depUuid);
  }
  virtual bool checkDependancesTree()
  {
    return m_dependancyHolder.checkDependances();
  }
  virtual bool dependsOf(const boost::uuids::uuid& depUuid)
  {
    ServicePtr<AbstractService> ptr(depUuid);
    if (ptr)
      return ptr->addDependant(this->uuid());
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
    return m_initialized
  }
  virtual void setInitilizationStatus(bool status)
  {
    m_initialized = status;
  }
};

} // namespace services 
