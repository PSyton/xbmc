#pragma once
#include "ptr_invoker.h"
#include "core.h"

namespace services {

class CorePtr
  : public PtrInvoker<Core>
{
  static Core* m_core;
  Core* get();
  friend class Core;
public:
  CorePtr();
  bool isValid() const;
};

} // namespace services