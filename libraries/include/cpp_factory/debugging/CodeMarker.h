//
// Created by jaejunlee on 16. 4. 1.
//

#ifndef CPP_FACTORY_CODEMARKER_H
#define CPP_FACTORY_CODEMARKER_H
#include <iostream>
#include <string.h>
#include <stdio.h>
/*
 * Macro to extract file name(not full path)
 */
#define __FILENAME__    (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/')+1:__FILE__)


#ifdef USE_LOG_FUNC_LINE

// Write current function name and line number to 'os'.
#define LOG_FUNC_LINE(os)  \
os<<"["<<__PRETTY_FUNCTION__<<"/ Line "<<__LINE__<<"]"<<std::endl;
#else
#define LOG_FUNC_LINE(os)
#endif


#ifdef USE_LOG_MESSAGE
namespace __do_not_use__ {
    inline char *__getBuffer() {
        //TODO : make this thread-safe
        static char __msg_buffer[1024];
        return __msg_buffer;
    }
}

//Write formatted message to 'os'
#define LOG_MESSAGE(os, fmt, ...) {\
    sprintf(__do_not_use__::__getBuffer(), fmt, ##__VA_ARGS__);\
    os<<__do_not_use__::__getBuffer()<<"\n";}

//Write formatted message to 'os' with file name and line number.
#define LOG_MESSAGE_WITH_FNAME_LINE(os, fmt, ...) {\
    sprintf(__do_not_use__::__getBuffer(), fmt, ##__VA_ARGS__);\
    os<<__do_not_use__::__getBuffer()<<"["<<__FILENAME__<<":"<<__LINE__<<"]\n";}
#else
#define LOG_MESSAGE(os, fmt, ...)
#define LOG_MESSAGE_WITH_FNAME_LINE(os, fmt, ...)
#endif
#endif //CPP_FACTORY_CODEMARKER_H
