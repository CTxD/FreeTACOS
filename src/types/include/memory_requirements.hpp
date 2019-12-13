#ifndef MEMORY_REQUIREMENTS
#define MEMORY_REQUIREMENTS

#include "apex_process.h"
#include "general_types.hpp"

#include <circle/memio.h>
#include <cstdlib>

class MemoryRegion {
private:
    NAME_TYPE regionName;              /* required */
    memory_region_t type;              /* required */
    STACK_SIZE_TYPE size;              /* required */
    memory_access_t accessRights;      /* required */
    std::optional<decOrHex_t> address; /* optional */

    decOrHex_t freeMemory;

public:
    MemoryRegion(){};

    MemoryRegion(std::string name,
                 memory_region_t type,
                 STACK_SIZE_TYPE size,
                 memory_access_t accessRights,
                 std::optional<decOrHex_t> address)
        : regionName{name}, type{type}, size{size}, accessRights{accessRights}, address{address}
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

    MemoryRegion(const MemoryRegion& rhs)
        : regionName{rhs.regionName.name}, type{rhs.type}, size{rhs.size}, accessRights{rhs.accessRights}, address{rhs.address}
    {
    }

    const NAME_TYPE& getRegionName() const;

    const memory_region_t& getType() const;

    const STACK_SIZE_TYPE& getSize() const;

    const memory_access_t& getAccessRights() const;

    const std::optional<decOrHex_t>& getAddress() const;

    const RETURN_CODE_TYPE checkPointer(SYSTEM_ADDRESS_TYPE entryPtr,
                                        STACK_SIZE_TYPE size) const;

    RETURN_CODE_TYPE createContext(SYSTEM_ADDRESS_TYPE entryPtr, STACK_SIZE_TYPE size);
};

#endif
