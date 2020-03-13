#include "include/memory_area.hpp"

#ifdef HOST_TESTING
#include <cstring>
#else
#include <circle/alloc.h>
#include <circle/util.h>
#endif

MemoryArea::MemoryArea(void* ptr, size_t size)
{
    // filling with default value
    _area = memset(ptr, 0, size);
}

MemoryArea::~MemoryArea()
{
}

size_t MemoryArea::size() const noexcept
{
    return _size;
}

char* MemoryArea::data() const noexcept
{
    return static_cast<char*>(_area);
}
