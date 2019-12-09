#ifndef MEMORY_REQUIREMENTS
#define MEMORY_REQUIREMENTS

#include "apex_process.h"
#include "general_types.hpp"

#include <circle/memio.h>
#include <cstdlib>

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
    NAME_TYPE regionName;              /* required */
    memory_region_t type;              /* required */
    decOrHex_t size;                   /* required */
    memory_access_t accessRights;      /* required */
    std::optional<decOrHex_t> address; /* optional */

    decOrHex_t freeMemory;

public:
    MemoryRegion(){};

    MemoryRegion(NAME_TYPE name, memory_region_t type, decOrHex_t size, memory_access_t accessRights, decOrHex_t address)
        : regionName(name), type(type), size(size), accessRights(accessRights), address(address)
    {
        if (!address)
            address = 0;

        switch (type) {
        case memory_region_t::RAM:
            // code block
            break;
        case memory_region_t::FLASH:
            // code block
            break;
        case memory_region_t::INPUT_OUTPUT:
            break;
        default:
            // code block
            break;
        }
    }

    const NAME_TYPE& getRegionName() const;

    const memory_region_t& getType() const;

    const decOrHex_t& getSize() const;

    const memory_access_t& getAccessRights() const;

    const std::optional<decOrHex_t>& getAddress() const;

    RETURN_CODE_TYPE checkPointer(SYSTEM_ADDRESS_TYPE entryPtr, decOrHex_t size) const;

    RETURN_CODE_TYPE createContext(SYSTEM_ADDRESS_TYPE entryPtr, decOrHex_t size);
};

#endif
