#pragma once
#include "detail/listener_trait.h"
#include "detail/handler_predeclaration.h"
#include "upal/core/guarded/guarded_holder.h"
#include "upal/core/critical_section_guardian.h"
#include "upal/core/method/method0.h"
#include <boost/type_traits/is_pod.hpp>
#include <boost/static_assert.hpp>


namespace upal {
  namespace handlers {

    template <typename R>
    class BaseHandler<R (void)>
      : public GuardedHolder
    {
      typedef BaseHandler<R (void)> ThisType;
      typedef upal::method<R ()> ListenerFunction;
      ListenerFunction m_handler;

    public:
      BaseHandler() {}
      template <typename ListenerFunc, class ListenerClass>
      explicit BaseHandler(const ListenerFunc& handlerPtr, ListenerClass* receiverPtr)
        : GuardedHolder( detail::ListenerTrait<ListenerClass>().trait( receiverPtr ) )
        , m_handler( upal::bind_method( handlerPtr, receiverPtr ) )
      {}

      R operator()() const
      {
        return invoke();
      }

      R invoke() const
      {        
        upal::CriticalSectionGuardian  criticalSectionGuardian( &(getGuard().criticalSection()) );
        if ( m_handler && guarded() )
          return m_handler();

        return R();
      }

      ~BaseHandler()
      {
        BOOST_STATIC_ASSERT( ( boost::is_void<R>::value ) ||
          !( boost::is_pod<R>::value ) );
      }
      typedef ListenerFunction ThisType::*unspecified_bool_type;
      operator unspecified_bool_type() const // never throws
      {
        return ( m_handler && guarded() ) ? &ThisType::m_handler : 0;
      }
    };

  } // namespace handlers
} // namespace upal 
