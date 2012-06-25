#pragma once


namespace upal
{

  //! Создание уникальных типов  с поведением целочисленного типа
  template<typename T>
  class int_type
    : public T
  {
    int m_val;

  public:
    int_type(int a_val)
      : m_val(a_val)
    {}

    int value() const
    {
      return m_val;
    }

    operator int()
    {
      return m_val;
    }

    bool operator ==(int_type& a_other) const
    {
      return m_val == a_other.m_val;
    }

    bool operator !=(int_type& a_other) const
    {
      return !operator==();
    }
  };


  namespace detail
  {
    namespace statemachine
    {
      template <class T> 
      inline unsigned int sm_hash(const int_type<T>& key) { return (unsigned int)(key.value()); }
    }//namespace statemachine
  }//namespace detail

}//namespace upal
