#ifndef MONOTONIC_ALLOCATOR
#define MONOTONIC_ALLOCATOR

#include "monotonic_memory_resource.hpp"

template <typename T, typename Resource = MonotonicMemoryResource<>>
class MonotonicAllocator {
    Resource* _res;

public:
    using value_type = T;

    static_assert(alignof(T) <= Resource::alignment,
                  "Given type cannot be allocator with the given resource");

    explicit MonotonicAllocator()
    {
    }

    explicit MonotonicAllocator(Resource& res) : _res(&res)
    {
    }

    MonotonicAllocator(const MonotonicAllocator&) = default;

    template <typename U>
    MonotonicAllocator(const MonotonicAllocator<U>& other)
        : MonotonicAllocator(other.resource())
    {
    }

    Resource& resource() const
    {
        return *_res;
    }

    T* allocate(std::size_t n)
    {
        return static_cast<T*>(_res->allocate(sizeof(T) * n));
    }
    void deallocate(T* ptr, std::size_t)
    {
        _res->deallocate(ptr);
    }

    friend bool operator==(const MonotonicAllocator& lhs, const MonotonicAllocator& rhs)
    {
        return lhs._res == rhs._res;
    }

    friend bool operator!=(const MonotonicAllocator& lhs, const MonotonicAllocator& rhs)
    {
        return lhs._res != rhs._res;
    }
};

#endif
