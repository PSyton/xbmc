#pragma once
#include "const_reference_support.h"
#include "value_reference_support.h"

namespace upal
{
  //! ������ ��������� ����������� �������� �� �������
  struct reference_support
    : public const_reference_support
    , public value_reference_support
  {};

}//namespace upal
