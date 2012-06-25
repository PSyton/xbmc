#pragma once
#include "service_meta.h"

namespace ack {
namespace core {

class DependancyHolder;

class InterfaceStorage;

class AbstractService 
{
protected:
  virtual InterfaceStorage& storage() = 0;
  friend class BaseInterfaceMixin;
  virtual void shutdown() = 0;
public:
  virtual ~AbstractService() {};
  virtual const CStdString& description() const = 0;
  virtual const CStdString& name() const = 0;
  virtual const boost::uuids::uuid& uuid() const = 0;
  
  virtual bool init() = 0;
  virtual bool resolveDependances() = 0;
  virtual void onInit() = 0;
  virtual void onShutdown() = 0;
  
  virtual bool addDependent(const boost::uuids::uuid& depUuid) = 0;
  virtual void removeDependent(const boost::uuids::uuid& depUuid) = 0;
  virtual bool checkDependencesTree() = 0;

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

} // namespace core
} // namespace ack

#define DECLARE_SERVICE_ENTRY(ParentIFace, IFaceClass, uuidString, n, d) \
private:\
  static const ack::core::BaseServiceMeta& meta()\
  {\
    static ack::core::SerivceMeta<IFaceClass> s_meta(uuidString, CStdString(n), CStdString(d));\
    return s_meta;\
  }\
protected:\
  IFaceClass() {}\
  virtual ~IFaceClass()\
  {\
    BOOST_STATIC_ASSERT( (boost::is_base_of<ack::core::AbstractService, ParentIFace>::value) );\
  }\
public:\
  static const boost::uuids::uuid& rootUuid() { return meta().uuid(); }\
  virtual const CStdString& description() const { return meta().name(); }\
  virtual const CStdString& name() const { return meta().description(); }\
private:\

