#include <tacoskerneltest.hpp>
#include <apex_buffer_tests.hpp>
#include <apex_mutex_tests.hpp>

#include <arch.h>


void setup(){
    CLogger::Get()->Write("APEX TEST", LogNotice,
                              "---------- Starting apex tests ----------");
    TestCreateBufferOutput();
    TestCreateMutexOutput();
    
    CLogger::Get()->Write("APEX TEST", LogNotice,
                              "-------- All apex tests are done --------");
    while(1){}
}