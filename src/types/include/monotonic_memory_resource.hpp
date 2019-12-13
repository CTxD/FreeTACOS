#ifndef MONOTONIC_MEMORY_RESOURCE
#define MONOTONIC_MEMORY_RESOURCE

#include <apex_types.h>
#include <atomic>
#include <circle/types.h>

static const int MAX_ALLIGN = 16;

template <size_t align = MAX_ALLIGN>
class MonotonicMemoryResource {
    std::atomic<char*> ptr;
    size_t freeSpace;

public:
    template <typename Area, typename = decltype(std::declval<Area&>().data())>
    explicit MonotonicMemoryResource(Area& a)
        : ptr(a.data()), freeSpace(a.size())
    {
    }

    constexpr static auto alignment = align;

    void* allocate(size_t size) noexcept{
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


    void deallocate(void*) noexcept {}
};

#endif
