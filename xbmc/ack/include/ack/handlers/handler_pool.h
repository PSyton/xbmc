#pragma once
#include <boost/unordered/unordered_map.hpp>
#include <boost/unordered/unordered_set.hpp>
#include <assert.h>
#include "threads/CriticalSection.h"

template <class L>
class TryLockWithTimeout
{
  L& m_lock;
  bool m_acquired;
public:
  TryLockWithTimeout(L& lock, int timeout)
    : m_lock(lock)
    , m_acquired(false)
  {
    utils::WaitCondition condition = upal::bind_method(&TryLockWithTimeout<L>::cantLock, this);
    m_acquired = lazy_wait(condition, 1, timeout);
  }
  ~TryLockWithTimeout()
  {
    if (m_acquired)
      m_lock.unlock();
  }
  bool cantLock()
  {
    return !m_lock.try_lock();
  }
  bool isLocked() const
  {
    return m_acquired;
  }
};

class GuardedObject;

//! Callback pool
/** This class holds list of homogeneous callbacks (handlers) without return values.
 * \param HandlerType - type of callback functor
 */
template <typename HandlerType>
class HandlerPool
{
  typedef boost::unordered_map<GuardedObject*, HandlerType>  HandlerList;
  typedef boost::unordered_set<GuardedObject*>                ForRemoval;
  typedef HandlerPool<HandlerType> this_type;
  HandlerList m_list;
  ForRemoval  m_forRemoval;
  CCriticalSection m_lock; //!< lock object

  CCriticalSection& lock()
  {
    return m_lock;
  }
  int waitInterval() const
  {
    return 10000;
  }
  class SafeDeleter
  {
    HandlerType m_handler;
  private:
    SafeDeleter(const HandlerType& h)
      : m_handler(h)
    {
    }
    ~SafeDeleter()
    {
      if (m_handler.destroyAfterInvoke() && m_handler.object())
        m_handler.object()->safeDelete();
    }
  };
public:
  HandlerPool()
  {}

  void clear()
  {
    m_list.clear();
  }

  //! Add callback object to pool
  bool addHandler(const HandlerType& h)
  {
    if ( h.object() )
    {
      upal::GuardedObject* guardPtr = static_cast<upal::GuardedObject*>( h.object() );
      // we cant add handlers from partially constructed objects (in the middle of construction).
      if( h.isConstructing() )
      {
        assert(0);
        return false;
      }
      // We don't need use lock here
      m_list.insert(guardPtr, h);
    }
    return true;
  }
  
  //! Remove callback object from pool
  void removeHandler(const HandlerType& h)
  {
    m_forRemoval.insert(h.object());
  }


  //! Remove all non-usable.
  void performRemoval()
  {
     typename ForRemoval::iterator it = m_forRemoval.begin();
     while ( it != m_forRemoval.end() )
     {
       m_list.erase(m_list.find(*it));
       m_forRemoval.erase(it);
       it = m_forRemoval.begin();
     }
  }


  void operator()()
  {
    invoke();
  }

  void invoke()
  {
    TryLockWithTimeout l(lock(), waitInterval());
    if (l.isLocked())
    {
      performRemoval();
      typename HandlerList::iterator it = m_list.begin();
      while ( it != m_list.end() )
      {
        if ( ( *it ).isDestroyed() )
          m_list.erase(it++);
        else
        {
          SafeDeleter deleter( *it );
          ( *(it++) )();
        }
      }
      return;
    }
    assert(0);
  }


  template <typename T1>
  void operator()(const T1& arg1)
  {
    invoke(arg1);
  }

  template <typename T1>
  void invoke(const T1& arg1)
  {
    TryLockWithTimeout l(lock(), waitInterval());
    if (l.isLocked())
    {
      performRemoval();
      typename HandlerList::iterator it = m_list.begin();
      while ( it != m_list.end() )
      {
        if ( ( *it ).isDestroyed() )
          m_list.erase( it++ );
        else
        {
          SafeDeleter deleter( *it );
          ( *(it++) )( arg1 ); 
        }
      }
      return;
    }
    assert(0);
  }

  template <typename T1, typename T2>
  void operator()(const T1& arg1, const T2& arg2)
  {
    invoke(arg1, arg2);
  }

  template <typename T1, typename T2>
  void invoke(const T1& arg1, const T2& arg2)
  {
    TryLockWithTimeout l(lock(), waitInterval());
    if (l.isLocked())
    {
      performRemoval();
      typename HandlerList::iterator it = m_list.begin();
      while ( it != m_list.end() )
      {
        if ( ( *it ).isDestroyed() )
          m_list.erase( it++ );
        else
        {
          SafeDeleter deleter( *it );
          ( *(it++) )( arg1, arg2 ); 
        }
      }
      return;
    }
    assert(0);
  }


  template <typename T1, typename T2, typename T3>
  void operator()(const T1& arg1, const T2& arg2, const T3& arg3)
  {
    invoke(arg1, arg2, arg3);
  }

  template <typename T1, typename T2, typename T3>
  void invoke(const T1& arg1, const T2& arg2, const T3& arg3)
  {
    TryLockWithTimeout l(lock(), waitInterval());
    if (l.isLocked())
    {
      performRemoval();
      typename HandlerList::iterator it = m_list.begin();
      while ( it != m_list.end() )
      {
        if ( ( *it ).isDestroyed() )
          m_list.erase( it++ );
        else
        {
          SafeDeleter deleter( *it );
          ( *(it++) )( arg1, arg2, arg3 ); 
        }
      }
      return;
    }
    assert(0);
  }


  template <typename T1, typename T2, typename T3, typename T4>
  void operator()(const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4)
  {
    invoke(arg1, arg2, arg3, arg4);
  }

  template <typename T1, typename T2, typename T3, typename T4>
  void invoke(const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4)
  {
    TryLockWithTimeout l(lock(), waitInterval());
    if (l.isLocked())
    {
      performRemoval();
      typename HandlerList::iterator it = m_list.begin();
      while ( it != m_list.end() )
      {
        if ( ( *it ).isDestroyed() )
          m_list.erase( it++ );
        else
        {
          SafeDeleter deleter( *it );
          ( *(it++) )( arg1, arg2, arg3, arg4 ); 
        }
      }
      return;
    }
    assert(0);
  }

  template <typename T1, typename T2, typename T3, typename T4, typename T5>
  void operator()(const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5)
  {
    invoke(arg1, arg2, arg3, arg4, arg5);
  }

  template <typename T1, typename T2, typename T3, typename T4, typename T5>
  void invoke(const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4, const T5& arg5)
  {
    TryLockWithTimeout l(lock(), waitInterval());
    if (l.isLocked())
    {
      performRemoval();
      typename HandlerList::iterator it = m_list.begin();
      while ( it != m_list.end() )
      {
        if ( ( *it ).isDestroyed() )
          m_list.erase( it++ );
        else
        {
          SafeDeleter deleter( *it );
          ( *(it++) )( arg1, arg2, arg3, arg4, arg5 ); 
        }
      }
      return;
    }
    assert(0);
  }
};
