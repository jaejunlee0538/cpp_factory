//
// Created by ub1404 on 16. 4. 23.
//

#ifndef CPP_FACTORY_BOOST_RANDOM_HPP_H
#define CPP_FACTORY_BOOST_RANDOM_HPP_H

#include <boost/random.hpp>
namespace cpp_factory {
    namespace random_boost{
        template<typename DistributionType, typename GeneratorType=boost::mt19937>
        struct RandomGenerator {
            typedef typename DistributionType::result_type RetType;
            typedef boost::variate_generator<GeneratorType, DistributionType> VariateGeneratorType;

            RandomGenerator(const DistributionType &dist) {
                GeneratorType gen(time(NULL));
                _getrnd.reset(new VariateGeneratorType(gen, dist));
            }

            RetType operator()() {
                return _getrnd->operator()();
            }

        private:
            boost::shared_ptr<VariateGeneratorType> _getrnd;
        };

        template<typename RetType, typename GeneratorType=boost::mt19937>
        struct NormallyDistributedNumber
                : public RandomGenerator<boost::normal_distribution<RetType>, GeneratorType> {
            NormallyDistributedNumber(const RetType &mean, const RetType &dev) :
                    RandomGenerator<boost::normal_distribution<RetType>, GeneratorType>(
                            boost::normal_distribution<RetType>(mean, dev)) { }

        };

        template<typename RealType, typename GeneratorType=boost::mt19937>
        struct UniformlyDistributedRealNumber
                : public RandomGenerator<boost::random::uniform_real_distribution<RealType>,
                        GeneratorType> {
            typedef RealType RetType;
            typedef boost::random::uniform_real_distribution<RealType> DistType;

            UniformlyDistributedRealNumber(const RetType &min_value, const RetType &max_value) :
                    RandomGenerator<DistType, GeneratorType>(DistType(min_value, max_value)) { }

        };

        template<typename IntType, typename GeneratorType=boost::mt19937>
        struct UniformlyDistributedIntNumber
                : public RandomGenerator<boost::random::uniform_int_distribution<IntType>,
                        GeneratorType> {
            typedef IntType RetType;
            typedef boost::random::uniform_int_distribution<IntType> DistType;

            UniformlyDistributedIntNumber(const RetType &min_value, const RetType &max_value) :
                    RandomGenerator<DistType, GeneratorType>(DistType(min_value, max_value)) { }

        };
    }
}
#endif //CPP_FACTORY_BOOST_RANDOM_HPP_H
