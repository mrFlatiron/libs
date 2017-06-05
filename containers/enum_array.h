#ifndef ENUM_ARRAY_H
#define ENUM_ARRAY_H
#include <vector>

template<class Enum, class T>
class enum_array
{
private:
  std::vector<T> m_vals;
  size_t m_size;
public:
  enum_array ();
  ~enum_array ();
  T &operator[] (Enum i);
  size_t size () const;
  T *data ();
};

template<class Enum, class T>
enum_array<Enum, T>::enum_array ()
{
  m_size = (size_t)(Enum::COUNT);
  m_vals.resize (m_size);
}

template<class Enum, class T>
enum_array<Enum, T>::~enum_array ()
{

}

template<class Enum, class T>
T &enum_array<Enum, T>::operator[] (Enum i)
{
 size_t index = (size_t)i;
 return m_vals[index];
}

template<class Enum, class T>
size_t enum_array<Enum, T>::size () const
{
  return m_size;
}

template<class Enum, class T>
T *enum_array<Enum, T>::data()
{
  return m_vals.data ();
}

#endif // ENUM_ARRAY_H
