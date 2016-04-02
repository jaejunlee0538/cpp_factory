//
// Created by jaejunlee on 16. 4. 2.
//

#ifndef CPP_FACTORY_SIMPLEPROFILER_H
#define CPP_FACTORY_SIMPLEPROFILER_H
#include <map>
#include <vector>
#include <stack>
#include <cpp_factory/clock/PreciseClock.h>

namespace __do_not_use_this_ {
    typedef std::vector<double> RunInfo;
    typedef std::map<std::string, RunInfo> FunctionMap;
    inline FunctionMap *getFunctionMap() {
        static FunctionMap functionMap;
        return &functionMap;
    }

    struct ___FFFFFFFFF {
        ___FFFFFFFFF(const std::string &func_name) : func_name(func_name) { }

        ~___FFFFFFFFF() {
            double t_elapsed = elapsedTime.getElapsedTime_sec();
            FunctionMap *map = getFunctionMap();
            FunctionMap::iterator it = map->find(func_name);
            if (it == map->end()) {
                RunInfo info;
                info.push_back(t_elapsed);
                map->insert(FunctionMap::value_type(func_name, info));
                return;
            }

            it->second.push_back(t_elapsed);
        }

        cpp_factory::ElapsedTime elapsedTime;
        std::string func_name;
    };

    typedef std::stack<___FFFFFFFFF> ___FFF_STACK;

    inline void report(std::ostream& os){
        FunctionMap* map = getFunctionMap();
        FunctionMap::const_iterator it1 = map->begin();
        while(it1 !=map->end()){
            RunInfo::const_iterator it2 = it1->second.begin();
            RunInfo::const_iterator it2_end = it1->second.end();
            os<< it1->first<<":";
            while(it2 != it2_end){
                os<<*it2<<",";
                it2++;
            }
            it1++;
            os<<std::endl;
        }
    }
}

#define LOG_RUNNING_TIME           __do_not_use_this_::___FFFFFFFFF ___ff_f_(__PRETTY_FUNCTION__)
#define REPORT_RUNNING_TIME_LOG(stream)     __do_not_use_this_::report(stream)

#endif //CPP_FACTORY_SIMPLEPROFILER_H
