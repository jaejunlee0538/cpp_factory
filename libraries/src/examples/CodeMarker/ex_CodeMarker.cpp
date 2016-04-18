//
// Created by ub1404 on 16. 4. 1.
//
#include <unistd.h>
#include <iostream>
#include "MyClass1.h"
#include "MyClass2.h"
#define USE_LOG_MESSAGE //One can switch on macro 'LOG_MESSAGE' by defining USE_LOG_MESSAGE
#include "cpp_factory/debugging/CodeMarker.h"
#include "cpp_factory/clock/PreciseClock.h"
using  namespace cpp_factory;

void costlyFunction(){
    ElapsedTime runningTime;
    ::usleep(123450);
    LOG_MESSAGE(std::cerr, "%lf sec", runningTime.getElapsedTime_sec());
    LOG_MESSAGE_WITH_FNAME_LINE(std::cerr, "This is debug message");
}

int main(void){
    MyClass1 c1;
    MyClass2 c2;

    c1.myFunction();
    c2.myFunction();
    std::cerr<<"-----------------------------------"<<std::endl;
    for(int i=0;i<10;i++){
        costlyFunction();
    }
    return 0;
}