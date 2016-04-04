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
#include "cpp_factory/profiling/libProfiler.h"

using namespace std;

void myfunction(){
    PROFILER_START(myfunction);
    ::sleep(1);
    PROFILER_END();
}

pthread_t id1;
void*testThread(void *pData){
    id1 = pthread_self();
    int count = 200;
    while(count--){
        PROFILER_START(testThread);
        ::usleep(10000);
        PROFILER_END();
    }
    return NULL;
}

int main()
{
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, testThread, NULL);

    PROFILER_ENABLE;
    PROFILER_START(main);
    PROFILER_START(main_usleep);
    ::usleep(10000);::usleep(10000);
    ::usleep(10000);::usleep(10000);
    PROFILER_END();
    myfunction();

//    std::cout<<thread_id<<","<<id1<<std::endl;
    PROFILER_END();
    pthread_join(thread_id, NULL);

    testThread(NULL);
    LogProfiler();
    PROFILER_DISABLE;
    return 0;
}