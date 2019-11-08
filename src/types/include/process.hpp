#ifndef PROCESS_H
#define PROCESS_H


#include "apex_process.h"
#include "general_types.hpp"


class Process
{
    private:
      PROCESS_ATTRIBUTE_TYPE attributes;
      PROCESS_STATUS_TYPE status;

    public:
      Process() {}

      Process(PROCESS_ATTRIBUTE_TYPE attr, PROCESS_STATUS_TYPE status):
        attributes(std::move(attr)), status(std::move(status)) {}

      const PROCESS_STATUS_TYPE& getStatus() const;

      const PROCESS_ATTRIBUTE_TYPE& getAttributes() const;
};

#endif
