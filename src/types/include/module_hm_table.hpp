#ifndef MODULE_HM_TABLE
#define MODULE_HM_TABLE

#include "module_error_action.hpp"

class ModuleHMTable {
private:
    ModuleErrorAction moduleErrorAction[100];
    MemoryArea moduleErrorActionArea{std::data(moduleErrorAction),
                                     std::size(moduleErrorAction)};
    MonotonicMemoryResource<> moduleErrorActionSrc{moduleErrorActionArea};
    MonotonicAllocator<ModuleErrorAction> moduleErrorActionAllocator{moduleErrorActionSrc};
    identifier_t stateIdentifier; /* required */
    description_t description;    /* required */
    std::vector<ModuleErrorAction, MonotonicAllocator<ModuleErrorAction>> actions{
        moduleErrorActionAllocator}; /* required */

public:
    ModuleHMTable(){};

    ModuleHMTable(identifier_t state, std::string descr, std::initializer_list<ModuleErrorAction> actions)
        : stateIdentifier(state), actions(actions)
    {
        strcpy(description, descr.c_str());
    }

    ModuleHMTable(const ModuleHMTable& rhs)
        : stateIdentifier(rhs.stateIdentifier), actions(rhs.actions)
    {
        strcpy(description, rhs.description);
    }

    ModuleHMTable& operator=(const ModuleHMTable&);

    const identifier_t& getStateIdentifier() const;

    const description_t& getDescription() const;

    const std::vector<ModuleErrorAction, MonotonicAllocator<ModuleErrorAction>>& getActions() const;
};

#endif
