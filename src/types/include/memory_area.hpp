#ifndef MEMORY_AREA
#define MEMORY_AREA

#ifdef HOST_TESTING
#include <cstring>
#else
#include <circle/types.h>
#endif


class MemoryArea {
private:
    unsigned long _size = 0;
    void* _area = nullptr;

public:
    MemoryArea(void* ptr, unsigned long size);
    ~MemoryArea();

    size_t size() const noexcept;
    char* data() const noexcept;
};

#endif
