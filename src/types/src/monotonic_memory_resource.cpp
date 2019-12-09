#include "include/monotonic_memory_resource.hpp"

template <size_t align>
void* MonotonicMemoryResource<align>::allocate(size_t size) noexcept
{
    if (size >= freeSpace) {
        // Health monitor
    }
    freeSpace -= size;
    auto under = size % alignment;
    auto adjust_size = alignment - under;
    auto adjusted_size = size + adjust_size;
    auto ret = ptr.fetch_add(adjusted_size);
    return ret;
}

template <size_t align>
void MonotonicMemoryResource<align>::deallocate(void*) noexcept
{
}
