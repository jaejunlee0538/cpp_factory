//
// Created by ub1404 on 16. 3. 29.
//

#include <cpp_factory/ConsoleUtils.h>

using namespace cpp_factory;

struct MyStruct{
    int A;
    double B;
};

int main(){

    std::cerr<<"Int to hex"<<std::endl;
    std::cerr<<"\t"<<std::hex<<125<<"<-->";
    std::cerr<<toHex(125)<<std::endl;
    std::cerr<<"\t"<<std::hex<<3452<<"<-->";
    std::cerr<<toHex(3452)<<std::endl;

    std::cerr<<"Double to hex"<<std::endl;
    std::cerr<<"\t"<<3.141592<<"--->"<<toHex(3.141592)<<std::endl;

    std::cerr<<"char to hex"<<std::endl;
    std::cerr<<"\t"<<'A'<<"--->"<<toHex('A')<<std::endl;


    std::cerr<<"Struct to hex"<<std::endl;
    MyStruct m;
    m.A = 50;
    m.B = 3.145192;
    std::cerr<<"\t"<<toHex(m)<<std::endl;
    return 1;
}