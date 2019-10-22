#ifndef ALLOCATOR
#define ALLOCATOR

#include <atomic>
#include <cstddef>
#include <utility>
#include <unistd.h>
#include <sys/mman.h>
#include <system_error>


class MemoryArea {
  private:
    std::size_t area_size = 0;
    void* area = nullptr;
    int descriptor;         // file descriptor
    unsigned int offset;    // offset in the file

  public:
    MemoryArea(std::size_t size, int descrp = -1, unsigned int offset = 0)
    :area_size(size), descriptor(descrp), offset(offset) {
      area = ::mmap(nullptr,                      // memory area where to allocate (nullptr if it does not matter)
                    size,                         // bytes to be mapped
                    PROT_READ | PROT_WRITE,       // memory protection level
                    MAP_PRIVATE | MAP_ANONYMOUS,  // mapping attributes
                    descriptor,
                    offset);
      if(area == MAP_FAILED)
      {
        throw std::bad_alloc();
      }

      auto tail = data() + size - ::getpagesize();
      auto returnCode = ::mprotect(tail, ::getpagesize(), PROT_NONE);
      if(returnCode)
      {
        ::munmap(area, area_size);
        throw std::system_error(std::error_code(errno, std::system_category()),
                                "Protection of memory mapping [mprotect()] failed");
      }
    }

    ~MemoryArea()
    {
      if(area)
      {
        ::munmap(area, area_size);
      }
    }

    std::size_t size() const noexcept { return area_size; }
    char* data() const noexcept { return static_cast<char*>(area); }
};

template <std::size_t Alignment = sizeof(std::max_align_t)>
class MonotonicResource {
  private:
    std::atomic<char*> ptr;

  public:
    template <typename Area, typename = decltype(std::declval<Area&>().data())>
    MonotonicResource(Area& a): ptr(a.data()) {}

    constexpr static auto alignment = Alignment;

    void* allocate(std::size_t size) noexcept
    {
      auto under = size % Alignment;
      auto adjustSize = size + (Alignment - under);
      return ptr.fetch_add(adjustSize);
    }

    void deallocate(void*) noexcept {}
};

template <typename T, typename Resource = MonotonicResource<>>
class MonotonicAllocator {
  private:
    Resource* resource;

  public:
    static_assert(alignof(T) <= Resource::alignment,
                  "Given type cannot be allocated within the given resource. Its size is too big.");

    MonotonicAllocator(Resource& res): resource(&res) {}

    T* allocate(std::size_t size)
    {
        return static_cast<T*>(resource->allocate(sizeof(T) * size));
    }

    void deallocate(T* ptr, std::size_t)
    {
      resource->deallocate(ptr);
    }
};

#endif
