#ifndef PARTITION_HM_TABLE
#define PARTITION_HM_TABLE

#include "multipartition_hm_table.h"

class PartitionHMTable
{
  private:
    name_t tableName;                 /* required */
    name_t multiPartitionTableName;   /* required */
    std::vector<ErrorAction> actions; /* required */

    // Deprecated
    std::optional<identifier_t> tableIdentifier;  /* optional */
    identifier_t multiPartitionHMTableRef;        /* required */

  public:
    PartitionHMTable(name_t name, name_t multiPartitionHM, std::vector<ErrorAction> actions):
      tableName(name), multiPartitionTableName(multiPartitionHM), actions(actions) {}
};

#endif
