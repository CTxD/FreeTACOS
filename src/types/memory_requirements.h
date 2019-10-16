#include <string>

#include "general_types.h"

#ifndef MEMORY_REQUIREMENTS
#define MEMORY_REQUIREMENTS

class MemoryRequirements
{
  private:
    std::optional<nameType> regionName;               /* optional */
    std::string type;                                 /* required */
    decOrHexValueType sizeBytes;                      /* required */
    std::optional<decOrHexValueType> physicalAdress;  /* optional */
    std::string access;                               /* required */
};

#endif
