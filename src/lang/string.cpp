#include "string.h"

#include <string.h>


namespace common {

bool is_blank(const char *s)
{
  if (s == nullptr) {
    return true;
  }
  while (*s != '\0') {
    if (!isspace(*s)) {
      return false;
    }
    s++;
  }
  return true;
}

}

