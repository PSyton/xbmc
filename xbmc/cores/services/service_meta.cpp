#include "service_meta.h"
#include <boost/uuid/string_generator.hpp>


namespace services {

BaseServiceMeta::BaseServiceMeta(const char* sUuid, const CStdString& sName, const CStdString& sDescription)
  : m_uuid(boost::uuids::string_generator()(sUuid))
  , m_name(sName)
  , m_description(sDescription)
{
}


} // namespace services
