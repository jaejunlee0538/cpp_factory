//
// Created by ub1404 on 16. 4. 23.
//

#ifndef CPP_FACTORY_EASYCLOUDVIEWER_H
#define CPP_FACTORY_EASYCLOUDVIEWER_H
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <boost/thread.hpp>
namespace cpp_factory {
        /*
         * When compiled with c++11 and pre-built pcl binaries, CloudViewer spews SIGSEGV error.
         *      - PCL 1.7.2
         *      - Ubuntu 14.04 x64
         *      - gcc 4.8.4
         * You must compile PCL with c++11 flag enabled.
         */
        class EasyCloudViewer {
        public:
            template<typename cloud_ptr_type>
            EasyCloudViewer(const cloud_ptr_type input_cloud_ptr) {
                _cloud_viewer.reset(new pcl::visualization::CloudViewer("Easy Cloud Viewer"));
                _cloud_viewer->showCloud(input_cloud_ptr);
            }

            EasyCloudViewer(const pcl::PointCloud<pcl::PointXY>::Ptr input_cloud) {
                _cloud_viewer.reset(new pcl::visualization::CloudViewer("Easy Cloud Viewer"));

                pcl::PointCloud<pcl::PointXYZ>::Ptr _input_cloud_proxy(new pcl::PointCloud<pcl::PointXYZ>());
                _input_cloud_proxy->width = 0;
                _input_cloud_proxy->height = 1;
                for (size_t i = 0; i < input_cloud->size(); i++) {
                    pcl::PointXYZ tmp;
                    tmp.x = input_cloud->points[i].x;
                    tmp.y = input_cloud->points[i].y;
                    tmp.z = 0.0;
                    _input_cloud_proxy->push_back(tmp);
                }

                _cloud_viewer->showCloud(_input_cloud_proxy);
            }

            ~EasyCloudViewer() {
                if (!_cloud_viewer)
                    return;

                std::cerr << "Program is about to shut down. Please turn off the cloud viewer." << std::endl;
                while (!_cloud_viewer->wasStopped()) {

                }
            }

        protected:
            boost::shared_ptr<pcl::visualization::CloudViewer> _cloud_viewer;
        };

}
#endif //CPP_FACTORY_EASYCLOUDVIEWER_H
