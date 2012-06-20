#pragma once
#include "for_each_type.h"
#include <boost/unordered/unordered_map.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/shared_ptr.hpp>
#include "boost/checked_delete.hpp"


namespace services {

class AbstractServiceCreator
{
protected:
  AbstractServiceCreator() {}
  virtual ~AbstractServiceCreator() {}
  virtual AbstractService* create() = 0;
  virtual void destroy(AbstractService*) = 0;
}

template <class T>
class DefaultServiceCreator
  : public AbstractServiceCreator
{
public:
  DefaultServiceCreator() {}
  virtual ~DefaultServiceCreator() {}
  virtual AbstractService* create()
  {
    return new T();
  }
  virtual void destroy(AbstractService* service)
  {
    boost::checked_deleter<AbstractService>()(service);
  }
};

template <class ClassesList>
class ServiceFactory
{
private:
  typedef boost::shared_ptr<AbstractServiceCreator> CreatorPtr;
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
      CreatorPtr ptr(new DefaultServiceCreator<Type>());
      m_creators.insert(std::make_pair(Type::rootUuid(), ptr));
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

} // namespace services
