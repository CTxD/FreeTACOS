#ifndef PROCESS_H
#define PROCESS_H


#include "apex_process.h"
#include "general_types.hpp"


class Process
{
    private:
      PROCESS_ATTRIBUTE_TYPE attributes;
      PROCESS_STATUS_TYPE status;
      name_t      processName;
      decOrHex_t  processIdentifier;
      decOrHex_t  processPriority;
      decOrHex_t  processPeriod;
    public:
      Process(name_t name,
              decOrHex_t identifier,
              decOrHex_t priority,
              decOrHex_t period) 
              : processName(name),
                processIdentifier(identifier),
                processPriority(priority),
                processPeriod(period)
      {
      }

      Process() {}

      Process(PROCESS_ATTRIBUTE_TYPE attr, PROCESS_STATUS_TYPE status):
        attributes(std::move(attr)), status(std::move(status)) {}

      const PROCESS_STATUS_TYPE& getStatus() const;

      const PROCESS_ATTRIBUTE_TYPE& getAttributes() const;
};

#endif
