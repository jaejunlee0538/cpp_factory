//
// Created by ub1404 on 16. 3. 30.
//

#include "cpp_factory/files/FileUtils.h"
#include <boost/foreach.hpp>
using namespace cpp_factory;
int main(){
#ifndef BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
    FilesList filesList("/usr/include",RegexForFileExtensions("h"),
    cpp_factory::SortByName());

    BOOST_FOREACH(boost::filesystem::path p, filesList){
                    std::cout<<p.string()<<std::endl;
    }
#endif

    cpp_factory::LinuxHomeDir homeDir;
    std::cout<<"Home directory is : "<<homeDir<<std::endl;

    std::cout<<FileNameWithTimeStamp("bin","my_file")<<std::endl;



    return 1;
}