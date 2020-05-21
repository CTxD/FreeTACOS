#include <apex_buffer_tests.hpp>
#include <apex_buffer.hpp>
#include <partitionscheduling.hpp>
#include <arch.h>

void TestCreateBufferOutput(){
    CLogger::Get()->Write("APEX TEST", LogNotice, "Testing create buffer output");
    CyclicExecutiveSchedule::GetCurrentPartition()->partitionName = {
        "IOProcessing"};
    
    BUFFER_ID_TYPE id;
    RETURN_CODE_TYPE code;

    ApexBuffer::initialiseBuffers();

    CyclicExecutiveSchedule::GetCurrentPartition()->partitionName = {
        "asdasdasd"};
        
    ApexBuffer::CREATE_BUFFER({"TestBuffer"}, 255, 10, FIFO, &id, &code);
    assert(code == NOT_AVAILABLE);
    CLogger::Get()->Write("APEX TEST", LogNotice, "Creating buffer with non existing partition. return code NOT_AVAILABLE : PASSED");

    CyclicExecutiveSchedule::GetCurrentPartition()->partitionName = {
        "IOProcessing"};

    ApexBuffer::CREATE_BUFFER({"TestBuffer"}, 255, 10, FIFO, &id, &code);
    assert(code == NO_ERROR);
    CLogger::Get()->Write("APEX TEST", LogNotice, "Created buffer. return code NO_ERROR : PASSED");

    ApexBuffer::CREATE_BUFFER({"TestBuffer"}, 255, 10, FIFO, &id, &code);
    assert(code == INVALID_PARAM);
    CLogger::Get()->Write("APEX TEST", LogNotice, "Created existing buffer. return code INVALID_PARAM : PASSED");

}