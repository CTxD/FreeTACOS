#include <string>
#include <optional>

#ifndef GENERAL_TYPES
#define GENERAL_TYPES

typedef unsigned int identifierValueType;

#define MAX_NAME_LENGTH 30;

#define PARTITION_NUMBER 128;

#define MAX_NUMBER_MEMORY_REQUIREMENTS 100;

#define MAX_NUMBER_WINDOWS 200;

#define WINDOW_NUMBER 100;

#define CHANNEL_NUMBER 50;

#define MAX_NUMBER_MODULE_HM_TABLE 50;

typedef char[MAX_NAME_LENGTH] nameType;

typedef std::string decOrHexValueType;

#endif
