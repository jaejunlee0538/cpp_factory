//
// Created by ub1404 on 16. 4. 18.
//

#ifndef CPP_FACTORY_MEMBERCHECK_H
#define CPP_FACTORY_MEMBERCHECK_H

/*
 * Source :
 *  https://github.com/mariusmuja/flann/blob/master/src/cpp/flann/algorithms/all_indices.h
 */
#define DEFINE_TYPEDEF_CHECKER(TDEF) \
    template<typename T> \
    struct has_typedef_ ## TDEF { \
        typedef char No; \
        typedef long Yes; \
        template<typename C> static Yes test( typename C::TDEF* ); \
        template<typename C> static No test( ... ); \
        static bool const value = sizeof (test<T>(0))==sizeof(Yes);\
    }

#define HAS_TYPEDEF(CLASS, TDEF) \
    has_typedef_ ## TDEF<CLASS>::value

///////////////////Member checking requires c++11//////////////////////////////////////////////////
/*
 * Source :
 *  http://stackoverflow.com/questions/1005476/how-to-detect-whether-there-is-a-specific-member-variable-in-class
 */
#if __cplusplus > 201103L
//TODO : c++11 is required
#include <type_traits>
#define DEFINE_MEMBER_CHECKER(MEMBER) \
    template<typename T, typename V = bool> \
    struct has_member_ ## MEMBER : std::false_type { }; \
    template<typename T> \
    struct has_member_ ## MEMBER<T, \
        typename std::enable_if< \
            !std::is_same<decltype(std::declval<T>().MEMBER), void>::value, \
            bool \
            >::type \
        > : std::true_type { }

#define HAS_MEMBER(CLASS, MEMBER) \
    has_member_ ## MEMBER<CLASS>::value

#endif


/////////////////////////Example Code/////////////////////////////////////////////////////////////////
//#include <iostream>
//#include <iomanip>
//#include "cpp_factory/MemberCheck.h"
//
//struct X { typedef int id; };
//struct Y { int foo; };
//
//DEFINE_TYPEDEF_CHECKER(id);
//DEFINE_TYPEDEF_CHECKER(foo);
//DEFINE_MEMBER_CHECKER(id);
//DEFINE_MEMBER_CHECKER(foo);
//
//int main(void){
//
//    std::cout<<std::boolalpha;
//    std::cout<<"X has id member?\t"<<HAS_MEMBER(X, id)<<std::endl;
//    std::cout<<"X has foo member?\t"<<HAS_MEMBER(X, foo)<<std::endl;
//    std::cout<<"X has id type?\t"<<HAS_TYPEDEF(X, id)<<std::endl;
//    std::cout<<"X has foo type?\t"<<HAS_TYPEDEF(X, foo)<<std::endl;
//
//    std::cout<<"Y has id member?\t"<<HAS_MEMBER(Y, id)<<std::endl;
//    std::cout<<"Y has foo member?\t"<<HAS_MEMBER(Y, foo)<<std::endl;
//    std::cout<<"Y has id type?\t"<<HAS_TYPEDEF(Y, id)<<std::endl;
//    std::cout<<"Y has foo type?\t"<<HAS_TYPEDEF(Y, foo)<<std::endl;
//    return 0;
//}


#endif //CPP_FACTORY_MEMBERCHECK_H
