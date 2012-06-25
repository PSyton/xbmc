#pragma once

namespace ack {
namespace core {

class AbstractService;

namespace detail {

class AbstractServiceCreator
{
protected:
  AbstractServiceCreator() {}
  virtual ~AbstractServiceCreator() {}
  virtual AbstractService* create() = 0;
  virtual void destroy(AbstractService*) = 0;
};

} // namespace detail
} // namespace core
} // namespace ack
