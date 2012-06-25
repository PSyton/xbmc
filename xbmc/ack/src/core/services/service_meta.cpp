#include "ack/core/services/service_meta.h"
#include <boost/uuid/string_generator.hpp>


namespace ack {
namespace core {

BaseServiceMeta::BaseServiceMeta(const char* sUuid, const CStdString& sName, const CStdString& sDescription)
  : m_uuid(boost::uuids::string_generator()(sUuid))
  , m_name(sName)
  , m_description(sDescription)
{
}

bool BaseServiceMeta::addDependant(AbstractService* dependantPtr)
{
  return false;
}


} // namespace core
} // namespace ack
