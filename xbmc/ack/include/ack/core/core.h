#pragma once
#include "ack/core/core_global.h"
#include "ack/core/abstract_core.h"
#include "ack/core/services/abstract_service_factory.h"
#include "ack/pointer/pointer.h"
#include <list>

namespace ack {
namespace core {

class AbstractService;

class ACK_CORE_API Core
  : public AbstractCore
{
public:
  typedef Pointer<AbstractServiceFactory> FactoryPtr;
private:
  bool m_initialized;
  bool m_shutdown;
  typedef std::list<FactoryPtr> ServiceFactories;
public:
  Core();
  virtual ~Core();
  void initialize();

  // From AbstractCore
  virtual bool isValid() const;
  virtual AbstractService* getService(const boost::uuids::uuid& sUuid);
  virtual void shutdown();
  virtual bool isInitialized() const;
  virtual bool isTerminating() const;
};

} // namespace core
} // namespace ack
