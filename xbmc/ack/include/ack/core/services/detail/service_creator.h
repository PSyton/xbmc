#pragma once
#include "ack/core/services/detail/abstract_service_creator.h"
#include "ack/core/services/abstract_service.h"
#include "ack/guarded/guarded_object.h"
#include "boost/checked_delete.hpp"

namespace ack {
namespace core {
namespace detail {

template <class T>
class DefaultServiceCreator
  : public AbstractServiceCreator
{
public:
  DefaultServiceCreator() {}
  virtual ~DefaultServiceCreator() {}
  virtual AbstractService* create()
  {
    return GuardedFactory<T>::create();
  }
  virtual void destroy(AbstractService* service)
  {
    boost::checked_deleter<AbstractService>()(service);
  }
};

} // namespace detail
} // namespace core
} // namespace ack
