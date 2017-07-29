#ifndef ENUM_MISC_H
#define ENUM_MISC_H

#include "enum_range.h"
#include <cstring>

template<typename Enum, typename = use_if_enum<Enum>, typename = decltype (enum_to_string (Enum ()))>
Enum string_to_enum (const char *string)
{
  for (Enum e : enum_range<Enum> ())
    {
      if (!strcmp (enum_to_string (e), string))
        return e;
    }
  return enum_end (Enum ()); //implement enum_end (Enum) or Enum::COUNT;
}

#endif // ENUM_MISC_H
