#ifndef GENERAL_TYPES
#define GENERAL_TYPES

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

const unsigned long GIGABYT = 1024 * 1024 * 1024;

const APEX_INTEGER MAX_DESCRIPTION_LENGTH = 150;

typedef APEX_UNSIGNED identifier_t;

typedef APEX_INTEGER decOrHex_t;

typedef struct {
    NAME_TYPE x;
} name_t;

typedef char description_t[MAX_DESCRIPTION_LENGTH];

#endif