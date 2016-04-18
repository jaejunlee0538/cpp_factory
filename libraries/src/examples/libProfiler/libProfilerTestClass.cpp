//
// Created by ub1404 on 16. 4. 4.
//
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fstream>

#include "libProfilerTestClass.h"

void myPrintf(const char* str);

#define USE_PROFILER 1
#define LIB_PROFILER_IMPLEMENTATION
#define LIB_PROFILER_PRINTF myPrintf
#define LOG_ELAPSED_TIME_HISTORY 1
#include "cpp_factory/profiling/libProfiler.h"

libProfilerTestClass::libProfilerTestClass(){

    PROFILER_START(Constructor);
    //...
    PROFILER_END();

}


