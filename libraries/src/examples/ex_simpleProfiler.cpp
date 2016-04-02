//
// Created by ub1404 on 16. 4. 2.
//
#include <unistd.h>
#include <iostream>
#include "cpp_factory/profiling/simpleProfiler.h"

#define logstream  std::cerr

class MyClass{
public:
    void myFunction(){
        LOG_FUNCTION_RUNNING_TIME;
        ::usleep(123000);
    }
};

void happyFunction(){
    ::usleep(123400);
    LOG_FUNCTION_RUNNING_TIME;
    ::usleep(321400);
}
int main(){
    {
        LOG_FUNCTION_RUNNING_TIME;
        ::usleep(100000);
    }

    MyClass c1;
    c1.myFunction();

    happyFunction();


    REPORT_RUNNING_TIME_LOG(std::cerr);
    return 0;
}