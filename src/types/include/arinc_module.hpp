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

    Partition partitionBuffer[100];
    std::vector<Partition>* partitions = new (&partitionBuffer) std::vector<Partition>;

    SystemError systemErrorBuffer[100];
    std::vector<SystemError>* systemErrors =
        new (&systemErrorBuffer) std::vector<SystemError>;

    MultiPartitionHMTable multiPartitionHMTableBuffer[100];
    std::vector<MultiPartitionHMTable>* multiPartitionHMTableBuffers =
        new (&multiPartitionHMTableBuffer) std::vector<MultiPartitionHMTable>;

    ModuleHMTable moduleHMTableBuffer[100];
    std::vector<ModuleHMTable>* moduleHMTableBuffers =
        new (&moduleHMTableBuffer) std::vector<ModuleHMTable>;

    PartitionHMTable partitionHMBuffer[125];
    std::vector<PartitionHMTable>* partitionHMBuffers =
        new (&partitionHMBuffer) std::vector<PartitionHMTable>;

    vector<SystemError> systemErrorsTable;               /* required */
    vector<MultiPartitionHMTable> multiPartitionHMTable; /* required */
    vector<ModuleHMTable> moduleHMTable;                 /* required */
    vector<PartitionHMTable> partitionHMTable;           /* required */

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
            multiPartitionHMTableBuffers->push_back(m);
        }
        for (auto m : moduleHMTab) {
            moduleHMTableBuffers->push_back(m);
        }
        for (auto p : partitionHMTab) {
            partitionHMBuffers->push_back(p);
        }
    }

    const name_t& getModuleName() const;

    const std::optional<name_t>& getModuleVersion() const;

    const std::optional<APEX_INTEGER>& getModuleId() const;

    const vector<SystemError>& getSystemErrorsTable() const;

    const vector<PartitionHMTable>& getPartitionHmTable() const;

    const vector<Partition>& getPartitions() const;

    const vector<MultiPartitionHMTable>& getMultiPartitionHMTable() const;

    const vector<ModuleHMTable>& getModuleHmTable() const;

    const vector<PartitionHMTable>& getPartitionHMTable() const;

    const vector<Process>& getProcess() const;
};

#endif
