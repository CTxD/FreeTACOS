#ifndef MEMORY_REQUIREMENTS
#define MEMORY_REQUIREMENTS

#include "general_types.h"

class MemoryRequirements
{
  private:
    std::optional<NameType> regionName;               /* optional */
    std::string type;                                 /* required */
    DecOrHexValueType sizeBytes;                      /* required */
    std::optional<DecOrHexValueType> physicalAdress;  /* optional */
    std::string access;                               /* required */

  public:
    MemoryRequirements(NameType name, std::string type, DecOrHexValueType size,
                       DecOrHexValueType address, std::string access):
      regionName(name), type(type), sizeBytes(size), physicalAdress(address), access(access) {}

};

#endif
