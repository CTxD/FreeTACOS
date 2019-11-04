#ifndef MODULE_HM_TABLE
#define MODULE_HM_TABLE

#include "error_action.h"


class ModuleHMTable
{
    private:
      identifier_t stateIdentifier;           /* required */
      std::string description;                /* required */
      std::vector<ModuleErrorAction> actions; /* required */

    public:
      ModuleHMTable(identifier_t state, std::string descr, std::vector<ModuleErrorAction> actions):
        stateIdentifier(state), description(descr), actions(std::move(actions)) {}
      //
      // ModuleHMTable(const ModuleHMTable& p):
      //   stateIdentifier(p.stateIdentifier), description(p.description), actions(p.actions) {}
      //
      // ModuleHMTable(ModuleHMTable&& p) noexcept:
      //   stateIdentifier(std::move(p.stateIdentifier)), description(std::move(p.description)), actions(std::move(p.actions)) {}

      // ~ModuleHMTable() = default;
};

#endif
