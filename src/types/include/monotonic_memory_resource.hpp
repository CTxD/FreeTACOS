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

    void* allocate(size_t size) noexcept;

    void deallocate(void*) noexcept;
};

#endif
