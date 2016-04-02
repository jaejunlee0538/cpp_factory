//
// Created by ub1404 on 16. 4. 1.
//

#include "MyClass1.h"
#include <iostream>
#define USE_LOG_FUNC_LINE
#define USE_LOG_MESSAGE
#include "cpp_factory/debugging/CodeMarker.h"

void MyClass1::myFunction(){
    std::cerr<<"MyClass1 : "<<std::endl;
    LOG_FUNC_LINE(std::cerr);
    LOG_MESSAGE(std::cerr, "LOG_MESSAGE is enabled in MyClass1.");
}