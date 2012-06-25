#include "ack/core/core_ptr.h"
#include "ack/core/services/base_service.h"
#include "ack/core/services/service_meta.h"
#include <unittest++/UnitTest++.h>

TEST(CorePtrNullTest)
{
  CHECK(!ack::core::CorePtr());
}

TEST(CoreCreated)
{
  ack::core::Core c;
  CHECK(ack::core::CorePtr()->isValid());
}

class IA
  : public ack::core::AbstractService
{
  DECLARE_SERVICE_ENTRY(ack::core::AbstractService, IA, "5D1E2655-85EC-474C-BBA5-39AF68384A73", "i_a", "i_a descr")
public:
  virtual bool test1() const = 0;
};

class A
  : public ack::core::BaseService<IA>
{
public:
  virtual bool test1() const
  {
    return true;
  }
};

TEST(ServiceCreation)
{
  A a;
  CHECK_EQUAL(a.test1(), true);
}
