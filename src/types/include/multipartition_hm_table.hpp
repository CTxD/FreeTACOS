#ifndef MULTIPARTITION_HM_TABLE
#define MULTIPARTITION_HM_TABLE

#include "multipartition_error_action.hpp"


class MultiPartitionHMTable
{
  private:
    MultiPartitionErrorAction multiPartitionErrorAction[100];
    monotonic_buffer_resource multiPartitionErrorActionSrc{std::data(multiPartitionErrorAction),
                                                           std::size(multiPartitionErrorAction)};
    name_t tableName;                                   /* required */
    vector<MultiPartitionErrorAction> errorActions;      /* required */

  public:
    MultiPartitionHMTable() {}

    MultiPartitionHMTable(name_t name, std::initializer_list<MultiPartitionErrorAction> actions):
      tableName(name), errorActions(actions, &multiPartitionErrorActionSrc) {}

    MultiPartitionHMTable(const MultiPartitionHMTable& rhs):
      tableName(rhs.tableName), errorActions(rhs.errorActions) {}

    MultiPartitionHMTable& operator=(const MultiPartitionHMTable&);

    const name_t& getTableName() const;

    const vector<MultiPartitionErrorAction>& getActions() const;
};

#endif
