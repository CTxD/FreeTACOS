#ifndef ERROR_ID_LEVEL
#define ERROR_ID_LEVEL

#include "general_types.h"

enum error_level_t
{
    MODULE    = 0,
    PARTITION = 1,
    PROCESS   = 2,
};

enum error_code_t
{
    DEADLINE_MISSED     = 0,
    APPLICATION_ERROR   = 1,
    NUMERIC_ERROR       = 2,
    ILLEGAL_REQUEST     = 3,
    STACK_OVERFLOW      = 4,
    MEMORY_VIOLATION    = 5,
    HARDWARE_FAULT      = 6,
    POWER_FAILURE       = 7,
};

class ErrorLevel
{
    private:
        identifier_t errorIdentifier;           /* required */
        std::optional<name_t> description;      /* optional */
        error_level_t error_level;              /* required */
        std::optional<error_code_t> error_code; /* optional */

    public:
        ErrorLevel(identifier_t id, name_t description, error_level_t level, error_code_t code):
          errorIdentifier(id), description(description), error_level(level), error_code(code) {}
};

#endif
