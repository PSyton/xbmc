#pragma once
#include "upal/core/traits/check_inheritance.h"
#include "upal/core/guarded/guarded_object.h"


namespace upal {
  namespace handlers {
    namespace detail {

      //! Проверка наследования
      template <class Listener>
      class ListenerTrait
        : public ::upal::traits::CheckInheritance<Listener, upal::GuardedObject>
      {
      public:
        ListenerTrait() {}
        upal::GuardedObject* trait(Listener* lPtr)
        {
          return static_cast<upal::GuardedObject*>(lPtr);
        }
      };

    } // namespace detail
  } // namespace handlers
} // namespace upal 
