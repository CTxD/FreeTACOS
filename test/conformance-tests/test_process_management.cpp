#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "include/partition.hpp"

#include <iostream>

struct ReturnBitStruct {
    unsigned int comp1 : 1;
    unsigned int comp2 : 1;
    unsigned int comp3 : 1;
    unsigned int comp4 : 1;
};

void ProcFunction()
{
}

ReturnBitStruct CheckCreate_Process(Partition& partition,
                                    PROCESS_ATTRIBUTE_TYPE attr,
                                    RETURN_CODE_TYPE& returnCode,
                                    identifier_t& id,
                                    PROCESS_STATUS_TYPE& state)
{
    ReturnBitStruct ret{1, 1, 1, 1};
    RETURN_CODE_TYPE returnValue;
    partition.createProcess(attr, id, returnValue);
    if (returnCode == returnValue) {
        returnCode = returnValue;
        ret.comp1 = 0;
    }
    if (returnCode == RETURN_CODE_TYPE::NO_ERROR) {
        ret.comp2 = 0;
        PROCESS_STATUS_TYPE stat;
        partition.getProcessStatus(id, stat, returnValue);
        if (returnValue == RETURN_CODE_TYPE::NO_ERROR) {
            returnCode = returnValue;
            ret.comp3 = 0;
            if (stat.PROCESS_STATE == PROCESS_STATE_TYPE::DORMANT) {
                ret.comp4 = 0;
            }
        }
    }
    return ret;
}

TEST_CASE("CREATE_PROCESS", "[API-PROC-0230]")
{
    SECTION("Master_Test")
    {
        Partition partition(
            1, 1, "Master", 100, 1000,
            {{"mainMemory", memory_region_t::RAM, 1048576, memory_access_t::READ_WRITE, {}}},
            {}, {});
        PROCESS_STATUS_TYPE status;

        SECTION("T-PI-PROC-0230:0011")
        {
            PROCESS_ATTRIBUTE_TYPE attributes{
                10,           5, (SYSTEM_ADDRESS_TYPE)ProcFunction,
                100,          1, DEADLINE_TYPE::SOFT,
                {"Process_1"}};

            SECTION("API-PROC-0230:0010, API-PROC-0230:0030")
            {
                identifier_t processId;
                RETURN_CODE_TYPE returnValue = RETURN_CODE_TYPE::NO_ERROR;
                CheckCreate_Process(partition, attributes, returnValue, processId, status);
                REQUIRE(returnValue == RETURN_CODE_TYPE::NO_ERROR);
                REQUIRE(processId);

                Process proc;
                partition.getProcess(processId, proc, returnValue);
                REQUIRE(proc.getStatus().PROCESS_STATE == PROCESS_STATE_TYPE::DORMANT);

                returnValue = RETURN_CODE_TYPE::NO_ACTION;
                CheckCreate_Process(partition, attributes, returnValue, processId, status);
                REQUIRE(returnValue == RETURN_CODE_TYPE::NO_ACTION);
            }
        }

        SECTION("T-API-PROC-0230:0015")
        {
            RETURN_CODE_TYPE returnValue = RETURN_CODE_TYPE::NO_ERROR;
            identifier_t proc1Id;
            identifier_t proc2Id;
            identifier_t proc3Id;

            PROCESS_ATTRIBUTE_TYPE attrProc1{INFINITE_TIME_VALUE,
                                             5,
                                             (SYSTEM_ADDRESS_TYPE)0x80000100,
                                             100,
                                             1,
                                             DEADLINE_TYPE::SOFT,
                                             {"Process_1"}};

            PROCESS_ATTRIBUTE_TYPE attrProc2{10,
                                             INFINITE_TIME_VALUE,
                                             (SYSTEM_ADDRESS_TYPE)0x80000200,
                                             100,
                                             1,
                                             DEADLINE_TYPE::SOFT,
                                             {"Process_2"}};

            PROCESS_ATTRIBUTE_TYPE attrProc3{INFINITE_TIME_VALUE,
                                             INFINITE_TIME_VALUE,
                                             (SYSTEM_ADDRESS_TYPE)0x80000300,
                                             100,
                                             1,
                                             DEADLINE_TYPE::SOFT,
                                             {"Process_3"}};

            SECTION(
                "API-PROC-0230:0016, API-PROC-0230:0013, API-PROC-0230:0018")
            {
                CheckCreate_Process(partition, attrProc1, returnValue, proc1Id, status);
                REQUIRE(returnValue == RETURN_CODE_TYPE::NO_ERROR);
                REQUIRE(proc1Id);

                CheckCreate_Process(partition, attrProc2, returnValue, proc2Id, status);
                REQUIRE(returnValue == RETURN_CODE_TYPE::NO_ERROR);
                REQUIRE(proc2Id);

                CheckCreate_Process(partition, attrProc3, returnValue, proc3Id, status);
                REQUIRE(returnValue == RETURN_CODE_TYPE::NO_ERROR);
                REQUIRE(proc3Id);

                bool uniqueIds = proc1Id != proc2Id || proc1Id != proc3Id ||
                                 proc2Id != proc3Id;
                REQUIRE(uniqueIds);
            }
        }

        SECTION("T-API-PROC-0230:0012")
        {
            SECTION("API-PROC-0230:0040")
            {
                RETURN_CODE_TYPE returnValue = RETURN_CODE_TYPE::INVALID_PARAM;
                PROCESS_ATTRIBUTE_TYPE attributes{
                    10, 5, (SYSTEM_ADDRESS_TYPE)ProcFunction, 10000, 1, DEADLINE_TYPE::SOFT, {"Process_ERROR_HANDLING"}};
            }

            SECTION("API-PROC-0230:0050")
            {
                identifier_t processId;
                RETURN_CODE_TYPE returnValue = RETURN_CODE_TYPE::INVALID_PARAM;
                PROCESS_ATTRIBUTE_TYPE attributes{
                    10, 5, (SYSTEM_ADDRESS_TYPE)ProcFunction, 100, -1, DEADLINE_TYPE::SOFT, {"Process_ERROR_HANDLING"}};

                CheckCreate_Process(partition, attributes, returnValue, processId, status);
                REQUIRE(returnValue == RETURN_CODE_TYPE::INVALID_PARAM);

                attributes = PROCESS_ATTRIBUTE_TYPE{
                    10, 5, (SYSTEM_ADDRESS_TYPE)ProcFunction, 100, 100, DEADLINE_TYPE::SOFT, {"Process_ERROR_HANDLING"}};

                CheckCreate_Process(partition, attributes, returnValue, processId, status);
                REQUIRE(returnValue == RETURN_CODE_TYPE::INVALID_PARAM);
            }

            SECTION("API-PROC-0230:0060")
            {
                identifier_t processId;
                RETURN_CODE_TYPE returnValue = RETURN_CODE_TYPE::INVALID_PARAM;
                PROCESS_ATTRIBUTE_TYPE attributes{
                    -10, 5, (SYSTEM_ADDRESS_TYPE)ProcFunction, 100, 1, DEADLINE_TYPE::SOFT, {"Process_ERROR_HANDLING"}};

                CheckCreate_Process(partition, attributes, returnValue, processId, status);
                REQUIRE(returnValue == RETURN_CODE_TYPE::INVALID_PARAM);
            }

            SECTION("API-PROC-0230:0070")
            {
                identifier_t processId;
                RETURN_CODE_TYPE returnValue = RETURN_CODE_TYPE::INVALID_CONFIG;
                PROCESS_ATTRIBUTE_TYPE attributes{
                    33, 5, (SYSTEM_ADDRESS_TYPE)ProcFunction, 100, 1, DEADLINE_TYPE::SOFT, {"Process_ERROR_HANDLING"}};

                CheckCreate_Process(partition, attributes, returnValue, processId, status);
                REQUIRE(returnValue == RETURN_CODE_TYPE::INVALID_CONFIG);
            }

            SECTION("API-PROC-0230:0080")
            {
                identifier_t processId;
                RETURN_CODE_TYPE returnValue = RETURN_CODE_TYPE::INVALID_PARAM;
                PROCESS_ATTRIBUTE_TYPE attributes{
                    10, 12, (SYSTEM_ADDRESS_TYPE)ProcFunction, 100, 1, DEADLINE_TYPE::SOFT, {"Process_ERROR_HANDLING"}};

                CheckCreate_Process(partition, attributes, returnValue, processId, status);
                REQUIRE(returnValue == RETURN_CODE_TYPE::INVALID_PARAM);

                attributes = PROCESS_ATTRIBUTE_TYPE{
                    10, -5, (SYSTEM_ADDRESS_TYPE)ProcFunction, 100, 1, DEADLINE_TYPE::SOFT, {"Process_ERROR_HANDLING"}};
                REQUIRE(returnValue == RETURN_CODE_TYPE::INVALID_PARAM);
            }
            SECTION("API-PROC-0230:0090")
            {
                identifier_t processId;
                partition.setMode(OPERATING_MODE_TYPE::NORMAL);
                RETURN_CODE_TYPE returnValue = RETURN_CODE_TYPE::INVALID_MODE;
                PROCESS_ATTRIBUTE_TYPE attributes{
                    10, 5, (SYSTEM_ADDRESS_TYPE)ProcFunction, 100, 1, DEADLINE_TYPE::SOFT, {"Process_ERROR_HANDLING"}};
                CheckCreate_Process(partition, attributes, returnValue, processId, status);
                REQUIRE(returnValue == RETURN_CODE_TYPE::INVALID_MODE);
                REQUIRE(!processId);
            }
        }
    }
}
