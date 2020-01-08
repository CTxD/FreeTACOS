#ifndef MODULE_HM_TABLE
#define MODULE_HM_TABLE

#include "module_error_action.hpp"
#include <string.h>

class ModuleHMTable {
private:
    ModuleErrorAction moduleErrorAction[100];
    std::vector<ModuleErrorAction>* moduleErrorActions =
        new (&moduleErrorAction) std::vector<ModuleErrorAction>;

    identifier_t stateIdentifier;      /* required */
    description_t description;         /* required */
    vector<ModuleErrorAction> actions; /* required */

public:
    ModuleHMTable(){};

    ModuleHMTable(identifier_t state, std::string descr, std::initializer_list<ModuleErrorAction> actions)
        : stateIdentifier(state)
    {
        for (auto a : actions) {
            moduleErrorActions->push_back(a);
        }
        strcpy(description, descr.c_str());
    }

    ModuleHMTable(const ModuleHMTable& rhs)
        : stateIdentifier(rhs.stateIdentifier), actions(rhs.actions)
    {
        for (auto a : rhs.getActions()) {
            moduleErrorActions->push_back(a);
        }
        strcpy(description, rhs.description);
    }

    ModuleHMTable& operator=(const ModuleHMTable&);

    const identifier_t& getStateIdentifier() const;

    const description_t& getDescription() const;

    const vector<ModuleErrorAction>& getActions() const;
};

#endif
