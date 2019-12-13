#ifndef GENERAL_TYPES
#define GENERAL_TYPES

#ifdef HOST_TESTING
#include <cstring>
typedef std::size_t size_t;
#else
#include <circle/types.h>
#endif


#include "allocator.hpp"
#include "memory_area.hpp"
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include <apex_types.h>

const APEX_INTEGER PARTITION_NUMBER = 128;

const APEX_INTEGER MAX_NUMBER_MEMORY_REQUIREMENTS = 100;

const APEX_INTEGER MAX_NUMBER_SYSTEM_STATES = 2;

const APEX_INTEGER MAX_NUMBER_WINDOWS = 200;

const APEX_INTEGER WINDOW_NUMBER = 100;

const APEX_INTEGER CHANNEL_NUMBER = 50;

const APEX_INTEGER MAX_NUMBER_MODULE_HM_TABLE = 50;

const APEX_INTEGER MAX_DESCRIPTION_LENGTH = 150;

const PROCESSOR_CORE_ID_TYPE DEFAULT_PROCESS_CORE_AFFINITY = 0;

const APEX_INTEGER DEFAULT_ASSOCIATED_PROCESSOR_CORES = 1;

typedef APEX_UNSIGNED identifier_t;

typedef APEX_INTEGER decOrHex_t;

typedef char description_t[MAX_DESCRIPTION_LENGTH];

enum memory_region_t {
    RAM,
    FLASH,
    INPUT_OUTPUT,
};

enum memory_access_t {
    READ_WRITE,
    READ_ONLY,
};

#endif
