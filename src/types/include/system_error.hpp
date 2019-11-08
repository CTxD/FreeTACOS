#ifndef SYSTEM_ERROR
#define SYSTEM_ERROR

#include "general_types.hpp"


class SystemError
{
  private:
    identifier_t errorIdentifier; /* required */
    std::string description;      /* required */

  public:
    SystemError() {}

    SystemError(identifier_t id, std::string descr):
      errorIdentifier(id), description(descr) {}

    const identifier_t& getErrorId() const;

    const std::string& getDescription() const;
};

#endif
