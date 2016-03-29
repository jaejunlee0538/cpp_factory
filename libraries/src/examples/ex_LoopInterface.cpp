//
// Created by ub1404 on 16. 3. 29.
//
#include <iostream>
#include <cpp_factory/LoopInterface.h>

using namespace cpp_factory;
class LoopExample : public LoopInterface
{
public:
    LoopExample(){

    }
protected:

    virtual void signal_handler(int sig){
        std::cerr<<sig<<" is signaled."<<std::endl;
    }
};


int main(){
    LoopExample example;

    while(!example.should_stop()){

    }

    std::cerr<<"Bye Bye~"<<std::endl;
}

