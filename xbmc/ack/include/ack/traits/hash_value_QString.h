#pragma once
#include <QtCore/QString>

inline std::size_t hash_value(const QString& v)
{
  return static_cast<std::size_t>(qHash(v));
}
