#pragma once
#include "ack/for_each_type.h"
#include "ack/pointer/pointer.h"
#include "ack/core/services/detail/service_creator.h"

#include <boost/unordered/unordered_map.hpp>
#include <boost/uuid/uuid.hpp>


namespace ack {
namespace core {

template <class ClassesList>
class ServiceFactory
{
private:
  typedef Pointer<detail::AbstractServiceCreator> CreatorPtr;
  typedef boost::unordered_map<boost::uuids::uuid, CreatorPtr> Creators;

  class Generator
  {
    Creators& m_creators;
  public:
    Generator(Creators& aCreators)
      : m_creators(aCreators)
    {
    }
    template<class Type>
    void operator()()
    {
      m_creators.insert( std::make_pair( Type::rootUuid()
                       , CreatorPtr( new DefaultServiceCreator<Type>() ) ) );
    }
  };

  explicit BaseServiceFactory(const BaseServiceFactory &);
  Creators m_creators;
private:
  AbstractServiceCreator* find(const boost::uuids::uuid& aUuid)
  {
    Creators::iterator it = m_creators.find(servicePtr->rootUuid());
    if (it != m_creators.end())
      return it->second.get();
    return 0;
  }
protected:
  inline Creators& creators()
  {
    return m_creators;
  }
public:
  ServiceFactory()
  {
    ::algorithm::for_each_type<ClassesList>(Generator(creators()));
  }
  virtual ~ServiceFactory() {}
  virtual AbstractService* createService(const boost::uuids::uuid& aUuid)
  {
    AbstractServiceCreator* cPtr = find(servicePtr->rootUuid());
    if (cPtr)
      return cPtr->create();
    return 0;
  }
  virtual void destroy(AbstractService* servicePtr)
  {
    if (servicePtr)
    {
      AbstractServiceCreator* cPtr = find(servicePtr->rootUuid());
      if (cPtr)
        cPtr->destroy(servicePtr);
      servicePtr = 0;
    }
  }
  UuidList uuidsList() const
  {
    UuidList list;
    for (Creators::const_iterator it = m_creators.begin(); it != m_creators.end(); ++it)
      list.push_back(it->first);
    return list;
  }
  bool canCreate(const boost::uuids::uuid& aUuid) const
  {
    return (m_creators.find(aUuid) != m_creators.end());
  }
};

} // namespace core
} // namespace ack


#define IMPLEMENT_SERVICE_FACTORY(FactoryClassName, ServicesTypeList) \
\
class FactoryClassName\
  : public ack::core::ServiceFactory<ServicesTypeList>\
{\
public:\
  FactoryClassName()\
    : ack::core::ServiceFactory<ServicesTypeList>()\
  {}\
  ~FactoryClassName()\
  {}\
  virtual const char *name() const { return #FactoryClassName; }\
};
