#pragma once
#include "detail/listener_trait.h"
#include "detail/handler_predeclaration.h"
#include "upal/core/guarded/guarded_holder.h"
#include "upal/core/critical_section_guardian.h"
#include "upal/core/method/method5.h"
#include <boost/type_traits/is_pod.hpp>
#include <boost/static_assert.hpp>


namespace upal {
  namespace handlers {

    template <typename A1, typename A2, typename A3, typename A4, typename A5, typename R>
    class BaseHandler<R (A1, A2, A3, A4, A5)>     
      : public GuardedHolder
    {
      typedef BaseHandler<R (A1, A2, A3, A4, A5)> ThisType;
      typedef upal::method<R (A1, A2, A3, A4, A5)> ListenerFunction;
      ListenerFunction m_handler;

    public:
      BaseHandler() {}
      template <typename ListenerFunc, class ListenerClass>
      explicit BaseHandler(const ListenerFunc& handlerPtr, ListenerClass* receiverPtr)
        : GuardedHolder( detail::ListenerTrait<ListenerClass>().trait( receiverPtr ) )
        , m_handler( upal::bind_method( handlerPtr, receiverPtr ) )
      {}

      R operator()(A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5 ) const
      {
        return invoke(arg1, arg2, arg3, arg4, arg5);
      }

      R invoke(A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5) const
      {
        upal::CriticalSectionGuardian  criticalSectionGuardian( &(getGuard().criticalSection()) );
        if ( m_handler && guarded() )
          return m_handler( arg1, arg2, arg3, arg4, arg5 );

        return R();
      }

      ~BaseHandler()
      {
        BOOST_STATIC_ASSERT( !( boost::is_void<A1>::value ) );
        BOOST_STATIC_ASSERT( !( boost::is_void<A2>::value ) );
        BOOST_STATIC_ASSERT( !( boost::is_void<A3>::value ) );
        BOOST_STATIC_ASSERT( !( boost::is_void<A4>::value ) );
        BOOST_STATIC_ASSERT( !( boost::is_void<A5>::value ) );
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
