#ifndef PARTITION_HM_TABLE
#define PARTITION_HM_TABLE

#include "multipartition_hm_table.h"


class PartitionHMTable
{
  private:
    PartitionErrorAction partitionErrorAction[100];
    monotonic_buffer_resource partitionErrorActionSrc{std::data(partitionErrorAction),
                                                      std::size(partitionErrorAction)};
    name_t tableName;                           /* required */
    name_t multiPartitionTableName;             /* required */
    vector<PartitionErrorAction> actions;       /* required */

  public:
    PartitionHMTable() {};
    PartitionHMTable(name_t name, name_t multiPartitionHM, std::initializer_list<PartitionErrorAction> actions):
      tableName(name), multiPartitionTableName(multiPartitionHM), actions(actions, &partitionErrorActionSrc) {}
};

#endif
