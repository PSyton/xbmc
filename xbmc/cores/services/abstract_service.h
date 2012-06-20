#pragma once
#include <boost/uuid/uuid.hpp>
#include "service_meta.h"


namespace services {
class DependancyHolder;

class InterfaceStorage;

class AbstractService 
{
protected:
  virtual InterfaceStorage& storage() = 0;
  friend class BaseInterfaceMixin;
public:
  virtual const CStdString& description() const = 0;
  virtual const CStdString& name() const = 0;
  virtual const boost::uuids::uuid& uuid() const = 0;
  virtual ~AbstractService();
  
  virtual bool init() = 0;
  virtual bool testDependences() = 0;
  virtual bool addDependant(boost::uuids::uuid&, DependancyHolder* servicePtr) = 0;
  virtual void removeDependant(boost::uuids::uuid&) = 0;
  virtual bool registerDependancy(boost::uuids::uuid&) = 0;

  virtual void onInitComplete() = 0;
  virtual void onBeforeShutdown() = 0;
  
  virtual bool isInitialized() const = 0;
  virtual void setInitilizationStatus(bool status) = 0;
};

#define DECLARE_SERVICE_ENTRY(ParentIFace, IFaceClass, uuidString, n, d) \
private:\
  static const BaseServiceMeta& meta()\
  {\
    statuc ServiceMeta<IFaceClass> s_meta(uuidString, CStdString(n), CStdString(d));\
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
  virtual StdString description() const { return meta().name(); }\
  virtual StdString name() const { return return meta().description() }\
private:\



} // namespace services

