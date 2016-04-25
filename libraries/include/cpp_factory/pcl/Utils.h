//
// Created by ub1404 on 16. 4. 24.
//

#ifndef CPP_FACTORY_UTILS_H
#define CPP_FACTORY_UTILS_H
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>

namespace cpp_factory {
        template<typename RndGen, typename PointT>
        struct RandomPointGenerator {
            RandomPointGenerator(RndGen gen) : _gen(gen) { }

            PointT operator()() const {
                PointT p;
                p.x = _gen();
                p.y = _gen();
                p.z = _gen();
                return p;
            }

            RndGen &_gen;
        };

        template<typename RndGen>
        struct RandomPointGenerator<RndGen, pcl::PointXY> {
            RandomPointGenerator(RndGen gen) : _gen(gen) { }

            pcl::PointXY operator()() const {
                pcl::PointXY p;
                p.x = _gen();
                p.y = _gen();
                return p;
            }

            RndGen &_gen;
        };

        template<typename PointT, typename RndGen>
        typename pcl::PointCloud<PointT>::Ptr createRandomPointCloud(RndGen gen, size_t num_points) {
            RandomPointGenerator<RndGen, PointT> _gen(gen);
            typename pcl::PointCloud<PointT>::Ptr cloud(new pcl::PointCloud<PointT>());
            cloud->resize(num_points);
            for (size_t i = 0; i < num_points; i++) {
                cloud->points[i] = _gen();
            }
            return cloud;
        }
}
#endif //CPP_FACTORY_UTILS_H
