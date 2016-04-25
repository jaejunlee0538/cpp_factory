//
// Created by ub1404 on 16. 4. 18.
//
#include <iostream>
#include <iomanip>
#include "cpp_factory/MemberCheck.h"

struct X { typedef int id; };
struct Y { int foo; };

DEFINE_TYPEDEF_CHECKER(id);
DEFINE_TYPEDEF_CHECKER(foo);
#if __cplusplus > 201103L   //check c++11 flag
DEFINE_MEMBER_CHECKER(id);
DEFINE_MEMBER_CHECKER(foo);
#endif

int main(void){

    std::cout<<std::boolalpha;
#if __cplusplus > 201103L
    std::cout<<"X has id member?\t"<<HAS_MEMBER(X, id)<<std::endl;
    std::cout<<"X has foo member?\t"<<HAS_MEMBER(X, foo)<<std::endl;
#endif
    std::cout<<"X has id type?\t"<<HAS_TYPEDEF(X, id)<<std::endl;
    std::cout<<"X has foo type?\t"<<HAS_TYPEDEF(X, foo)<<std::endl;

#if __cplusplus > 201103L
    std::cout<<"Y has id member?\t"<<HAS_MEMBER(Y, id)<<std::endl;
    std::cout<<"Y has foo member?\t"<<HAS_MEMBER(Y, foo)<<std::endl;
#endif
    std::cout<<"Y has id type?\t"<<HAS_TYPEDEF(Y, id)<<std::endl;
    std::cout<<"Y has foo type?\t"<<HAS_TYPEDEF(Y, foo)<<std::endl;
    return 0;
}