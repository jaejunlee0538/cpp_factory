//
// Created by ub1404 on 16. 3. 30.
//

#include "cpp_factory/files/FileUtils.h"
#include <boost/foreach.hpp>
using namespace cpp_factory;
int main(){
#ifndef BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
    FilesList filesList("/home/ub1404/Downloads",RegexForFileExtensions("bmp,jpg,png"));

    BOOST_FOREACH(boost::filesystem::path p, filesList){
                    std::cout<<p.string()<<std::endl;
    }
#endif
    cpp_factory::LinuxHomeDir homeDir;
    std::cout<<homeDir+"/map"<<std::endl;

    std::cout<<FileNameWithTimeStamp("bin","my_file")<<std::endl;
    return 1;
}