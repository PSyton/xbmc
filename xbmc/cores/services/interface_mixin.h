#pragma once
#include "interface_storage.h"
#include "abstract_service.h"

namespace services {

template <InterfaceClass>
class InterfaceMixin
  : public InterfaceClass 
  , public BaseInterfaceMixin
{
  AbstractService* m_rootService;
public:
  InterfaceMixin(AbstractService* aRootService)
    : InterfaceClass()
    , m_rootService(aRootService)
  {
    rootStorage(m_rootService).registerInterface(InterfaceClass::interfaceUuid(), static_cast<void*>(this));
  }
  template <class A0>
  InterfaceMixin(AbstractService* aRootService, const A0 &a0)
    : InterfaceClass(a0)
    , m_rootService(aRootService)
  {
    rootStorage(m_rootService).registerInterface(InterfaceClass::interfaceUuid(), static_cast<void*>(this));
  }
  virtual ~InterfaceMixin() {}
  virtual AbstractService* rootService()
  {
    return m_rootService;
  }
};

#define DECLARE_SERVICE_INTERFACE(IFaceClass, iGUIDStr)\
protected:\
  IFaceClass() {}\
  virtual ~IFaceClass() {}\
  virtual services::AbstractService* rootService() = 0;\
public:\
  static const boost::uuids::uuid& interfaceUuid() {\
    static boost::uuids::uuid uuid(boost::uuids::string_generator()(sUuid));\
    return uuid;\
  }\
private:\


} // namespace services 
