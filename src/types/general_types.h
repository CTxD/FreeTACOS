#ifndef GENERAL_TYPES
#define GENERAL_TYPES

#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <optional>
#include <experimental/memory_resource>

const int MAX_NAME_LENGTH = 30;

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

char buffer[MAX_NAME_LENGTH];

typedef struct
{
  char x[MAX_NAME_LENGTH];
} name_t;

enum criticality_t
{
    LEVEL_A = 0,
    LEVEL_B = 1,
    LEVEL_C = 2,
    LEVEL_D = 3,
    LEVEL_E = 4,
};

enum affinity_t
{
  ANY     = 0,
  CORE_1  = 1,
  CORE_2  = 2,
  CORE_3  = 3,
  CORE_4  = 4,
};

#endif
