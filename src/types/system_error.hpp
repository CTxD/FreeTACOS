#ifndef SYSTEM_ERROR
#define SYSTEM_ERROR

#include "general_types.h"


class SystemError
{
  private:
    identifier_t errorIdentifier; /* required */
    std::string description;      /* required */

  public:
    SystemError(identifier_t id, std::string descr):
      errorIdentifier(id), description(descr) {}
};

#endif
