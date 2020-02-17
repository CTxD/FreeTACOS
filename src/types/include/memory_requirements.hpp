#ifndef MEMORY_REQUIREMENTS
#define MEMORY_REQUIREMENTS

#include "general_types.hpp"

enum memory_region_t {
    RAM,
    FLASH,
    INPUT_OUTPUT,
};

enum memory_access_t {
    READ_WRITE,
    READ_ONLY,
};

class MemoryRegion {
private:
    name_t regionName;                 /* required */
    memory_region_t type;              /* required */
    decOrHex_t size;                   /* required */
    memory_access_t accessRights;      /* required */
    std::optional<decOrHex_t> address; /* optional */

public:
    MemoryRegion(){};

    MemoryRegion(name_t name, memory_region_t type, decOrHex_t size, memory_access_t accessRights, decOrHex_t address)
        : regionName(name), type(type), size(size), accessRights(accessRights), address(address)
    {
    }

    const name_t& getRegionName() const;

    const memory_region_t& getType() const;

    const decOrHex_t& getSize() const;

    const memory_access_t& getAccessRights() const;

    const std::optional<decOrHex_t>& getAddress() const;
};

#endif