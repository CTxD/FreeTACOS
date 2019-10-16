#ifndef GENERAL_TYPES
#define GENERAL_TYPES

#include <string>
#include <utility>
#include <optional>

typedef unsigned int IdentifierValueType;

const int MAX_NAME_LENGTH = 30;

const int PARTITION_NUMBER = 128;

const int MAX_NUMBER_MEMORY_REQUIREMENTS = 100;

const int MAX_NUMBER_WINDOWS = 200;

const int WINDOW_NUMBER = 100;

const int CHANNEL_NUMBER = 50;

const int MAX_NUMBER_MODULE_HM_TABLE = 50;

typedef struct
{
  char x[MAX_NAME_LENGTH];
} NameType;

typedef std::string DecOrHexValueType;

enum CriticalityType
{
    LEVEL_A = 0,
    LEVEL_B = 1,
    LEVEL_C = 2,
    LEVEL_D = 3,
    LEVEL_E = 4,
};

#endif
