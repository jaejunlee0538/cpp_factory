//
// Created by ub1404 on 16. 4. 24.
//
#include "cpp_factory/random/boost_random.h"
#include "cpp_factory/pcl/EasyCloudViewer.h"
#include "cpp_factory/pcl/Utils.h"

int main(){

    pcl::PointCloud<pcl::PointXY>::Ptr cloud =
            cpp_factory::createRandomPointCloud<pcl::PointXY>(
                    cpp_factory::random_boost::NormallyDistributedNumber<float>(0,3), 10000);

    cpp_factory::EasyCloudViewer viewer(cloud);


    return 0;
}