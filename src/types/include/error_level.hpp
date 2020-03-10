#ifndef ERROR_ID_LEVEL
#define ERROR_ID_LEVEL

#include "apex_error.hpp"
#include "general_types.hpp"

class ErrorLevel {
private:
    identifier_t errorIdentifier;              /* required */
    std::optional<name_t> description;         /* optional */
    ERROR_LEVEL_TYPE error_level;              /* required */
    std::optional<ERROR_CODE_TYPE> error_code; /* optional */

public:
    ErrorLevel(){};

    ErrorLevel(identifier_t id, name_t description, ERROR_LEVEL_TYPE level, ERROR_CODE_TYPE code)
        : errorIdentifier(id), description(description), error_level(level), error_code(code)
    {
    }

    const identifier_t& getErrorIdentifier() const;

    const std::optional<name_t>& getDescription() const;

    const ERROR_LEVEL_TYPE& getErrorLevel() const;

    const std::optional<ERROR_CODE_TYPE>& getErrorCode() const;
};

#endif
