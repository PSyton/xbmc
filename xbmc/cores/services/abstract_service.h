#pragma once
#include "service_meta.h"

namespace services {
class DependancyHolder;

class InterfaceStorage;

class AbstractService 
{
protected:
  virtual InterfaceStorage& storage() = 0;
  friend class BaseInterfaceMixin;
  virtual void shutdown() = 0;
public:
  virtual const CStdString& description() const = 0;
  virtual const CStdString& name() const = 0;
  virtual const boost::uuids::uuid& uuid() const = 0;
  virtual ~AbstractService();
  
  virtual bool init() = 0;
  virtual bool resolveDependances() = 0;
  virtual void onInit() = 0;
  virtual void onShutdown() = 0;
  
  virtual bool addDependant(const boost::uuids::uuid& depUuid) = 0;
  virtual void removeDependant(const boost::uuids::uuid& depUuid) = 0;
  virtual bool checkDependancesTree() = 0;

  virtual bool dependsOf(const boost::uuids::uuid& depUuid) = 0;
  
  virtual bool isInitialized() const = 0;
  virtual void setInitilizationStatus(bool status) = 0;
};

class BaseInterfaceMixin
{
protected:
  InterfaceStorage& rootStorage(AbstractService* aRootService)
  {
    return aRootService->storage();
  }
};

} // namespace services

#define DECLARE_SERVICE_ENTRY(ParentIFace, IFaceClass, uuidString, n, d) \
private:\
  static const services::BaseServiceMeta& meta()\
  {\
    static services::SerivceMeta<IFaceClass> s_meta(uuidString, CStdString(n), CStdString(d));\
    return s_meta;\
  }\
protected:\
  IFaceClass() {}\
  virtual ~IFaceClass()\
  {\
    BOOST_STATIC_ASSERT( (boost::is_base_of<services::AbstractService, ParentIFace>::value) );\
  }\
public:\
  static const boost::uuids::uuid& rootUuid() { return meta().uuid(); }\
  virtual const CStdString& description() const { return meta().name(); }\
  virtual const CStdString& name() const { return meta().description(); }\
private:\

