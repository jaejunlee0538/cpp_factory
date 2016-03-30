//
// Created by ub1404 on 16. 3. 30.
//

#include "cpp_factory/files/FileLister.h"
#include <boost/foreach.hpp>
using namespace cpp_factory;
int main(){
    FilesList filesList("/home/ub1404/Downloads",RegexForFileExtensions("bmp,jpg,png"), SortByExtension());

    BOOST_FOREACH(boost::filesystem::path p, filesList){
                    std::cout<<p.string()<<std::endl;
    }

    return 1;
}