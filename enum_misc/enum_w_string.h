#ifndef ENUM_W_STRING_H
#define ENUM_W_STRING_H

#include <cstring>
#include <cassert>
#include "enum_range.h"


template<class Enum>
const char *enum_to_string (Enum type);

template<class Enum>
Enum string_to_enum (const char *str)
{
  for (Enum type : enum_range<Enum> ())
    {
      const char *cmp = enum_to_string (type);
      if (!strcmp (str, cmp)) return type;
    }
  return enum_end<Enum> ();
}

#endif // ENUM_W_STRING_H
