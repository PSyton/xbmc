#pragma once
#include "ack/core/core_global.h"
#include "ack/pointer/ptr_invoker.h"

namespace ack {
namespace core {

class AbstractCore;

class ACK_CORE_API CorePtr
  : public PtrInvoker<AbstractCore>
{
  static AbstractCore* m_core;
  AbstractCore* get();
  friend class Core;
public:
  CorePtr();
  bool isValid() const;
};

} // namespace services
} // namespace ack
