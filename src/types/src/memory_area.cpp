#include "include/memory_area.hpp"

#include <circle/alloc.h>
#include <circle/memory.h>

MemoryArea::MemoryArea(void* ptr, size_t size)
{
	// filling with default value
    _area = memset(ptr, 0, size);
    if (_area == nullptr) {
        // health monitoring
    }
}

MemoryArea::~MemoryArea()
{}

size_t MemoryArea::size() const noexcept
{
    return _size;
}

char* MemoryArea::data() const noexcept
{
    return static_cast<char*>(_area);
}
