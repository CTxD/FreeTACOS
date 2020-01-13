#include "include/memory_requirements.hpp"

#ifdef HOST_TESTING
#include <cstring>
#include <iostream>
#else
#include <circle/util.h>
#endif

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
            // Entry point for address space is within the bounds
            return RETURN_CODE_TYPE::NO_ERROR;
        }
        // There is not enough of free space in this region
        return RETURN_CODE_TYPE::INVALID_PARAM;
    }
    return RETURN_CODE_TYPE::INVALID_CONFIG;
}

RETURN_CODE_TYPE MemoryRegion::createContext(SYSTEM_ADDRESS_TYPE entryPtr,
                                             STACK_SIZE_TYPE size,
                                             TTaskRegisters& m_Regs)
{
    // pok_thread_stack_addr
    // pok_space_context_create
    if (checkPointer(entryPtr, size) == RETURN_CODE_TYPE::NO_ERROR) {
        unsigned stack_addr = freeMemory;
        freeMemory += size;
        memset(&m_Regs, 0, sizeof(m_Regs));

        m_Regs.x0 = (u64)entryPtr;
        m_Regs.sp = (u64) new u8[TASK_STACK_SIZE] + stack_addr;
        m_Regs.x30 = (u64)&entryPtr;

        u32 nFPCR;
#ifndef HOST_TESTING
        asm volatile("mrs %0, fpcr" : "=r"(nFPCR));
#endif
        m_Regs.fpcr = nFPCR;
    }
    return RETURN_CODE_TYPE::NO_ERROR;
}
