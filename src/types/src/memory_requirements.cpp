#include "include/memory_requirements.hpp"

#include <circle/memory.h>

const NAME_TYPE& MemoryRegion::getRegionName() const
{
    return regionName;
}

const memory_region_t& MemoryRegion::getType() const
{
    return type;
}

const decOrHex_t& MemoryRegion::getSize() const
{
    return size;
}

const memory_access_t& MemoryRegion::getAccessRights() const
{
    return accessRights;
}

const std::optional<decOrHex_t>& MemoryRegion::getAddress() const
{
    return address;
}

RETURN_CODE_TYPE MemoryRegion::checkPointer(SYSTEM_ADDRESS_TYPE entryPtr, STACK_SIZE size)
{
    if (freeMemory >= size) {
        if (freeMemory - size <= (int)entryPtr) {
            return RETURN_CODE_TYPE::NO_ERROR;
        }
    }
    return RETURN_CODE_TYPE::INVALID_CONFIG;
}

void MemoryRegion::createContext(SYSTEM_ADDRESS_TYPE stackPtr,
                                 SYSTEM_ADDRESS_TYPE entryPtr,
                                 STACK_SIZE size)
{
    if (checkPointer(entryPtr, size) == RETURN_CODE::NO_ERROR) {
        // pok_thread_stack_addr
        // pok_space_context_create
    }
}
