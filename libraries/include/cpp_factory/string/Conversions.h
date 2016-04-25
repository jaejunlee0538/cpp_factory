//
// Created by ub1404 on 16. 3. 29.
//

#ifndef CPP_FACTORY_CONSOLEUTILS_H
#define CPP_FACTORY_CONSOLEUTILS_H
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <iomanip>
namespace cpp_factory{
    template <typename T>
    std::string toHex(const T& data){
        std::stringstream result;
        size_t len = sizeof(data);
        const unsigned char* pt = ((const unsigned char*)&data) + len-1;
        for(int i=1;i<=len;i++,pt--){
            result<<std::setfill('0')<<std::setw(2)<<std::hex<< static_cast<int>(*pt);

            if(i % 4 == 0){
                if(i % 32 == 0)
                    result<<"\n";
                else
                    result<<" ";
            }
        }

        return result.str();
    }
}

#endif //CPP_FACTORY_CONSOLEUTILS_H
