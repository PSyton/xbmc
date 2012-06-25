#pragma once
#include "detail/listener_trait.h"
#include "detail/handler_predeclaration.h"
#include "upal/core/guarded/guarded_holder.h"
#include "upal/core/critical_section_guardian.h"
#include "upal/core/method/method2.h"
#include <boost/type_traits/is_pod.hpp>
#include <boost/static_assert.hpp>


namespace upal {
  namespace handlers {

    template <typename A1, typename A2, typename R>
    class BaseHandler<R (A1, A2)>
      : public GuardedHolder
    {
      typedef BaseHandler<R (A1, A2)> ThisType;
      typedef upal::method<R (A1, A2)> ListenerFunction;
      ListenerFunction m_handler;

    public:
      BaseHandler() {}
      template <typename ListenerFunc, class ListenerClass>
      explicit BaseHandler(const ListenerFunc& handlerPtr, ListenerClass* receiverPtr)
        : GuardedHolder( detail::ListenerTrait<ListenerClass>().trait( receiverPtr ) )
        , m_handler( upal::bind_method( handlerPtr, receiverPtr ) )
      {}

      R operator()(A1 arg1, A2 arg2) const
      {
        return invoke(arg1, arg2);
      }

      R invoke(A1 arg1, A2 arg2) const
      {
        upal::CriticalSectionGuardian  criticalSectionGuardian( &(getGuard().criticalSection()) );
        if ( m_handler && guarded() )
          return m_handler( arg1, arg2 );

        return R();
      }

      ~BaseHandler()
      {
        BOOST_STATIC_ASSERT( !( boost::is_void<A1>::value ) );
        BOOST_STATIC_ASSERT( !( boost::is_void<A2>::value ) );
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
