#pragma once
#include "utils/StdString.h"
#include <boost/uuid/uuid.hpp>

namespace services {

class BaseServiceMeta
{
  boost::uuids::uuid m_uuid;
  CStdString m_name;
  CStdString m_description;
  // Prevent copy
  BaseServiceMeta(const BaseServiceMeta&);
  BaseServiceMeta& operator=(const BaseServiceMeta&);
protected:
  BaseServiceMeta(const char* sUuid, const CStdString& sName, const CStdString& sDescription);
public:
  inline const boost::uuids::uuid& uuid() const
  {
    return m_uuid;
  }
  inline const CStdString& name() const
  {
    return m_name;
  }
  inline const CStdString& description() const
  {
    return m_description;
  }
};

template <class InterfaceClass>
class SerivceMeta
  : public BaseServiceMeta
{
public:
  SerivceMeta(const char* sUuid, const CStdString& sName, const CStdString& sDescription)
    : BaseServiceMeta(sUuid, sName, sDescription)
  {
  }
};

} // namespace services
