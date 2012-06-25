#include "ack/core/lazy_wait.h"
#ifdef _WIN32
#include <Windows.h>
#endif

namespace ack {
namespace core {

bool lazy_wait(const WaitCondition& condition, unsigned long msecsInterval, unsigned long msecsMax)
{
  bool waitSuccess = true;
  unsigned long msecsWaited = 0;

  int i;
  for(i = 0; condition() && (i < 100); ++i)
  {};

  if(i < 100)
    return waitSuccess;
  else
  {
    Sleep(0);
    if(!condition())
      return waitSuccess;
  }

  while(condition())
  {
    Sleep(msecsInterval);
    msecsWaited += msecsInterval;
    if( ( msecsMax != 0 )
      && ( msecsWaited > msecsMax ) )
    {
      waitSuccess = false;
      break;
    }
  }
  return waitSuccess;
}

} // namespace core
} // namespace ack
