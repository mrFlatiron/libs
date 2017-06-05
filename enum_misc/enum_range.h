#ifndef ENUM_RANGE_H
#define ENUM_RANGE_H

#include "enum_helper.h"

template<class Enum>
Enum enum_begin ()
{
  return (Enum)0;
}

template<class Enum>
Enum enum_end ()
{
  return Enum::COUNT;
}

template<class Enum>
class enum_range
{
public:
  enum_range ();
  ~enum_range ();
  enum_helper<Enum> begin ();
  enum_helper<Enum> end ();
};

template <class Enum>
enum_range<Enum>::enum_range ()
{

}

template<class Enum>
enum_range<Enum>::~enum_range ()
{

}

template<class Enum>
enum_helper<Enum> enum_range<Enum>::begin ()
{
  return enum_helper<Enum> (enum_begin<Enum> ());
}

template<class Enum>
enum_helper<Enum> enum_range<Enum>::end ()
{
  return enum_helper<Enum> (enum_end<Enum> ());
}

#endif // ENUM_RANGE_H
