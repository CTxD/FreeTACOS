#include "include/memory_requirements.hpp"

const NAME_TYPE& MemoryRegion::getRegionName() const
{
    return regionName;
}

const memory_region_t& MemoryRegion::getType() const
{
    return type;
}

const STACK_SIZE_TYPE& MemoryRegion::getSize() const
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

const RETURN_CODE_TYPE MemoryRegion::checkPointer(SYSTEM_ADDRESS_TYPE entryPtr,
                                                  STACK_SIZE_TYPE sizeRequest) const
{
    if (size >= sizeRequest) {
        if ((decOrHex_t)freeMemory + sizeRequest <= (decOrHex_t)entryPtr + sizeRequest) {
            // print "Entry point for address space is out of bounds"
            return RETURN_CODE_TYPE::NO_ERROR;
        }
        return RETURN_CODE_TYPE::INVALID_PARAM;
        // print "There is not enough of free space in this region"
    }
    return RETURN_CODE_TYPE::INVALID_CONFIG;
}

RETURN_CODE_TYPE MemoryRegion::createContext(SYSTEM_ADDRESS_TYPE entryPtr, STACK_SIZE_TYPE size)
{
    if (checkPointer(entryPtr, size) == RETURN_CODE_TYPE::NO_ERROR) {
        // pok_thread_stack_addr
        // pok_space_context_create
    }
    return RETURN_CODE_TYPE::NO_ERROR;
}
