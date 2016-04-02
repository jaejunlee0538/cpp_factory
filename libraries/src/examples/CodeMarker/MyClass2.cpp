//
// Created by ub1404 on 16. 4. 1.
//

#include "MyClass2.h"
#include <iostream>
#define USE_LOG_MESSAGE
//#define USE_LOG_MESSAGE
#include "cpp_factory/debugging/CodeMarker.h"

void MyClass2::myFunction(){
    std::cerr<<"MyClass2 : "<<std::endl;
    LOG_FUNC_LINE(std::cerr);
    LOG_MESSAGE(std::cerr, "LOG_MESSAGE is enabled in MyClass2.");

}