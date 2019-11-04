#ifndef PARTITION_HM_TABLE
#define PARTITION_HM_TABLE

#include "multipartition_hm_table.h"


class PartitionHMTable
{
  private:
    name_t tableName;                           /* required */
    name_t multiPartitionTableName;             /* required */
    std::vector<PartitionErrorAction> actions;  /* required */

  public:
    PartitionHMTable(name_t name, name_t multiPartitionHM, std::vector<PartitionErrorAction> actions):
      tableName(name), multiPartitionTableName(multiPartitionHM), actions(actions) {}

    // PartitionHMTable(const PartitionHMTable& p):
    //   tableName(p.tableName), multiPartitionTableName(p.multiPartitionTableName),
    //   actions(p.actions) {}
    // //
    // PartitionHMTable(PartitionHMTable&& p) noexcept:
    //   tableName(std::move(p.tableName)), multiPartitionTableName(std::move(p.multiPartitionTableName)),
    //   actions(std::move(p.actions)) {}

    // ~PartitionHMTable() = default;
};

#endif
