#ifndef SYSTEM_ERROR
#define SYSTEM_ERROR

#include "general_types.hpp"


class SystemError
{
  private:
    identifier_t errorIdentifier; /* required */
    description_t description;      /* required */

  public:
    SystemError() {}

    SystemError(identifier_t id, std::string descr):
      errorIdentifier(id)
      {
        strcpy(description, descr.c_str());
      }

    const identifier_t& getErrorId() const;

    const description_t& getDescription() const;
};

#endif
