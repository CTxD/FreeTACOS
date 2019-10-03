#include <string>

#include "general_types.h"

#ifndef MEMORY_REQUIREMENTS
#define MEMORY_REQUIREMENTS

class MemoryRequirements
{
  private:
    std::optional<NameType> regionName;               /* optional */
    std::string type;                                 /* required */
    DecOrHexValueType sizeBytes;                      /* required */
    std::optional<DecOrHexValueType> physicalAdress;  /* optional */
    std::string access;                               /* required */
};

#endif
