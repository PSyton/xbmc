#pragma once
#include "ack/core/core_global.h"

namespace ack {
namespace core {

class InvokeCount;

class ACK_CORE_API InvokeGuardian
{
  InvokeCount*  m_counter;
  inline InvokeCount* counter()
  {
    return m_counter;
  }
public:
  InvokeGuardian(InvokeCount* a_counter);
  ~InvokeGuardian();
};

} // namespace core
} // namespace ack
