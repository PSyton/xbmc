#pragma once
#include "ptr_invoker.h"
#include "core_ptr.h"
#include "core.h"
#include "abstract_service.h"
#include "interface_storage.h"
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_base_of.hpp>


namespace services {

template <class CastType>
class CastHelper
  : public BaseInterfaceMixin
{
public:
  CastType* operator()(AbstractService* s, const boost::uuids::uuid& sUuid)
  {
    if (s)
      return static_cast<CastType*>(rootStorage(s).getInterface(sUuid));
    return 0;
  }
};

template <>
class CastHelper<AbstractService>
{
public:
  AbstractService* operator()(AbstractService* s, const boost::uuids::uuid&)
  {
    return s;
  }
};

template <class IFace>
class BasePtr
  : public PtrInvoker<IFace>
{
protected:
  typedef PtrInvoker<IFace> Ptr;
  CastHelper<IFace> m_cast;
  BasePtr()
    : Ptr(0)
  {
  }
  void fromAbstract(AbstractService* aPtr, const boost::uuids::uuid& aUuid)
  {
    Ptr::set(m_cast(aPtr, aUuid));
  }
  AbstractService* abstract(const boost::uuids::uuid& aUuid)
  {
    CorePtr core;
    if (core.isValid())
      return core->getService(aUuid);
    return 0;
  }
};

template <class IFace>
class ServicePtr
  : public BasePtr<IFace>
{
  typedef ServicePtr<IFace> ThisClass;
  friend class ServicesIterator;
  // when use it?? Protected, constract other iface from abstract pointer???? Maybe for service iterator???
  explicit ServicePtr(AbstractService* sPtr)
  {
    BasePtr<IFace>::fromAbstract(sPtr, boost::uuids::uuid());
  }
  typedef typename BasePtr<IFace>::Ptr Ptr;
public:
  explicit ServicePtr()
  {
    BOOST_STATIC_ASSERT((boost::is_base_and_derived<AbstractService, IFace>::value));
    BasePtr<IFace>::fromAbstract(BasePtr<IFace>::abstract(IFace::rootUuid()));
  }

  explicit ServicePtr(const boost::uuids::uuid& aUuid)
  {
    BasePtr<IFace>::fromAbstract(BasePtr<IFace>::abstract(aUuid), aUuid);
  }
  
  template <class AnotherIFace>
  bool isSame()
  {
    if ( Ptr::isValid() )
      return QString( Ptr::get()->uuid() ) == QString( AnotherIFace::rootUuid() );
    return false;
  }
};


template <class IFace>
class InterfacePtr
  : public BasePtr<IFace>
{
  typedef typename BasePtr<IFace>::Ptr Ptr;
public:
  InterfacePtr()
  {
  }
  InterfacePtr(const InterfacePtr<IFace>& other)
  {
    *this = other;
  }
  template <class T>
  InterfacePtr(const ServicePtr<T>& sPtr)
  {
    *this = sPtr;
  }

  InterfacePtr(const boost::uuids::uuid& sUuid)
  {
    BasePtr<IFace>::fromAbstract(BasePtr<IFace>::abstract(sUuid), sUuid);
  }
  
  template <class T>
  InterfacePtr<IFace>& operator=(const ServicePtr<T>& sPtr)
  {
    Ptr::set(0);
    if(sPtr)
      BasePtr<IFace>::fromAbstract(static_cast<AbstractService*>(sPtr.get()), IFace::rootUuid());
    return *this;
  }

  // need this???
  InterfacePtr<IFace>& operator=(const InterfacePtr<IFace>& other)
  {
    if (this != &other)
    {
      if (other)
        Ptr::set(other.get());
      else
        Ptr::set(0);
    }
    return *this;
  }
};

} // namespace services
