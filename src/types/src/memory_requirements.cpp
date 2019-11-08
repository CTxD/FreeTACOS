#include "include/memory_requirements.hpp"

const name_t& MemoryRegion::getRegionName() const
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
