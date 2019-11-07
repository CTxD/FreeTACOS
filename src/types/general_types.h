#ifndef GENERAL_TYPES
#define GENERAL_TYPES

#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <optional>
#include <experimental/memory_resource>

#include <apex_types.h>

#include <initializer_list>

#include <boost/container/pmr/vector.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>
#include <boost/container/pmr/monotonic_buffer_resource.hpp>

using namespace boost::container::pmr;

typedef memory_resource* allocator_type;

const int PARTITION_NUMBER = 128;

const int MAX_NUMBER_MEMORY_REQUIREMENTS = 100;

const int MAX_NUMBER_SYSTEM_STATES = 2;

const int MAX_NUMBER_WINDOWS = 200;

const int WINDOW_NUMBER = 100;

const int CHANNEL_NUMBER = 50;

const int MAX_NUMBER_MODULE_HM_TABLE = 50;

const unsigned long GIGABYTE = 1024 * 1024 * 1024;

typedef unsigned int identifier_t;

typedef int decOrHex_t;

typedef struct
{
  NAME_TYPE x;
} name_t;

#endif
