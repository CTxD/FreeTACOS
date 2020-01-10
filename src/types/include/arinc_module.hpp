#ifndef ARINC_MODULE
#define ARINC_MODULE

#include "channel.hpp"
#include "module_hm_table.hpp"
#include "multipartition_hm_table.hpp"
#include "partition.hpp"
#include "partition_hm_table.hpp"
#include "partition_memory.hpp"
#include "process.hpp"
#include "system_error.hpp"
#include <vector>

class ArincModule {
private:
    name_t moduleName;                    /* required */
    std::optional<name_t> moduleVersion;  /* optional */
    std::optional<APEX_INTEGER> moduleId; /* optional */

    Partition partition[1];
    std::vector<Partition>* partitions = new (&partition) std::vector<Partition>;

    SystemError systemError[1];
    std::vector<SystemError>* systemErrors =
        new (&systemError) std::vector<SystemError>;

    MultiPartitionHMTable multiPartitionHMTable[1];
    std::vector<MultiPartitionHMTable>* multiPartitionHMTables =
        new (&multiPartitionHMTable) std::vector<MultiPartitionHMTable>;

    ModuleHMTable moduleHMTable[1];
    std::vector<ModuleHMTable>* moduleHMTables =
        new (&moduleHMTable) std::vector<ModuleHMTable>;

    PartitionHMTable partitionHMTable[1];
    std::vector<PartitionHMTable>* partitionHMTables =
        new (&partitionHMTable) std::vector<PartitionHMTable>;

public:
    ArincModule(){};

    ArincModule(name_t name,
                std::optional<name_t> version,
                std::optional<identifier_t> id,
                std::initializer_list<Partition> part,
                std::initializer_list<SystemError> err,
                std::initializer_list<MultiPartitionHMTable> multiPartTab,
                std::initializer_list<ModuleHMTable> moduleHMTab,
                std::initializer_list<PartitionHMTable> partitionHMTab)
        : moduleName(name), moduleVersion(version), moduleId(id)
    {
        for (auto p : part) {
            partitions->push_back(p);
        }
        for (auto s : err) {
            systemErrors->push_back(s);
        }
        for (auto m : multiPartTab) {
            multiPartitionHMTables->push_back(m);
        }
        for (auto m : moduleHMTab) {
            moduleHMTables->push_back(m);
        }
        for (auto p : partitionHMTab) {
            partitionHMTables->push_back(p);
        }
    }

    const name_t& getModuleName() const;

    const std::optional<name_t>& getModuleVersion() const;

    const std::optional<APEX_INTEGER>& getModuleId() const;

    const std::vector<SystemError>& getSystemErrorsTable() const;

    const std::vector<PartitionHMTable>& getPartitionHMTable() const;

    const std::vector<Partition>& getPartitions() const;

    const std::vector<MultiPartitionHMTable>& getMultiPartitionHMTable() const;

    const std::vector<ModuleHMTable>& getModuleHmTable() const;

    const std::vector<Process>& getProcess() const;
};

#endif
