#ifndef MEMORY_AREA
#define MEMORY_AREA

#include <circle/alloc.h>
#include <circle/memory.h>
#include <circle/types.h>
#include <circle/util.h>

class MemoryArea {
    size_t _size = 0;
    void* _area = nullptr;

public:
    explicit MemoryArea(void* ptr, size_t size)
    {
        _area = memset(ptr, 0, size);
        if (_area == nullptr) {
            // health monitoring
        }
    }
    ~MemoryArea()
    {
        if (_area) {
            free(_area);
        }
    }

    size_t size() const noexcept
    {
        return _size;
    }
    char* data() const noexcept
    {
        return static_cast<char*>(_area);
    }
};

#endif
