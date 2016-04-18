#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fstream>

void myPrintf(const char* str){
//    static std::ofstream f("performance_log.txt");
//    f<<str;

    fprintf(stderr, "%s", str);
}

#define USE_PROFILER 1
#define LIB_PROFILER_IMPLEMENTATION
#define LIB_PROFILER_PRINTF myPrintf
#define LOG_ELAPSED_TIME_HISTORY 1
#include "cpp_factory/profiling/libProfiler.h"

#include "libProfilerTestClass.h"

using namespace std;

pthread_t id1;
void*testThread(void *pData){
    id1 = pthread_self();
    int count = 50;
    while(count--){
        PROFILER_START(testThread);
        ::usleep(10000);
        PROFILER_END();
    }
    return NULL;
}


void myfunction(){
    PROFILER_START(myfunction);
    ::usleep(rand()%10000);
    PROFILER_END();
}

int main()
{
    PROFILER_ENABLE;

    pthread_t thread_id;
    pthread_create(&thread_id, NULL, testThread, NULL);

    libProfilerTestClass testClass;
    PROFILER_START(main);
    PROFILER_START(main_usleep);
    ::usleep(10000);::usleep(10000);
    ::usleep(10000);

    PROFILER_END();
    for(int i=0;i<100;i++)
        myfunction();
    testThread(NULL);

    PROFILER_END();
    pthread_join(thread_id, NULL);

    LogProfiler();
    PROFILER_DISABLE;

    return 0;
}