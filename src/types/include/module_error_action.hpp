#ifndef MODULE_ERROR_ACTION
#define MODULE_ERROR_ACTION

#include "apex_error.h"
#include "general_types.hpp"


class ModuleErrorAction
{
  private:
    identifier_t errorIdentifier;        /* required */
    MODULE_RECOVERY_ACTION_TYPE action;  /* required */

  public:
    ModuleErrorAction() {}

    ModuleErrorAction(identifier_t id, MODULE_RECOVERY_ACTION_TYPE action):
      errorIdentifier(id), action(action) {}

    identifier_t getErrorIdentifier();

    MODULE_RECOVERY_ACTION_TYPE getAction();
};

#endif
