#ifndef ENUM_HELPER_H
#define ENUM_HELPER_H
template<class Enum>
class enum_helper
{
private:
  unsigned int m_pos;
public:
  enum_helper (Enum init);
  ~enum_helper ();
  enum_helper<Enum> &operator++ ();
  bool operator== (const enum_helper<Enum> &cmp) const;
  bool operator!= (const enum_helper<Enum> &cmp) const;
  Enum operator* () const;
};

template<class Enum>
enum_helper<Enum>::enum_helper (Enum init)
{
  m_pos = (unsigned int)init;
}

template<class Enum>
enum_helper<Enum>::~enum_helper ()
{

}

template<class Enum>
enum_helper<Enum> &enum_helper<Enum>::operator++ ()
{
  m_pos++;
  return *this;
}

template<class Enum>
bool enum_helper<Enum>::operator == (const enum_helper<Enum> &cmp) const
{
  return cmp.m_pos == m_pos;
}

template<class Enum>
bool enum_helper<Enum>::operator != (const enum_helper<Enum> &cmp) const
{
  return cmp.m_pos != m_pos;
}

template<class Enum>
Enum enum_helper<Enum>::operator* () const
{
  return (Enum)m_pos;
}
#endif // ENUM_HELPER_H
