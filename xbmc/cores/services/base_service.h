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
protected:
  virtual InterfaceStorage& storage()
  {
    return m_storage;
  }
public:
  BaseService()
    : m_initialized(false)
  {
    BOOST_STATIC_ASSERT( (boost::is_base_of<AbstractService, RootInterfaceClass>) );
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
  virtual bool testDependences()
  {
    return true;
  }
  virtual bool addDependant(boost::uuids::uuid& depUuid, DependancyHolder* holderPtr)
  {
    if (depUuid.is_nul())
      return false;
    m_dependancyHolder.add(depUuid, holderPtr);
    return m_dependancyHolder.checkDependences();
  }
  virtual void removeDependant(boost::uuids::uuid& depUuid)
  {
    m_dependancyHolder.remove(depUuid);
  }
  virtual bool registerDependancy(boost::uuids::uuid& depUuid)
  {
    ServicePtr ptr(depUuid);
    if (!ptr)
      return false;
    return ptr->addDependant(rootUuid(), &m_dependancyHolder);
  }
  template <class ServiceInterface>
  bool registerDependancy()
  {
    return registerDependancy(ServiceInterface::rootUuid());
  }
  virtual void onInitComplete()
  {
  }
  virtual void onBeforeShutdown()
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
}

} // namespace services 
