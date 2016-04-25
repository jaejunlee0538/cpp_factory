//
// Created by ub1404 on 16. 4. 23.
//

#include "cpp_factory/random/boost_random.h"
template<typename RndType>
void testRandom(RndType gen){
    for(int i=0;i<10;i++){
        std::cerr<<gen()<<",";
    }
    std::cerr<<std::endl;
}

int main(){
    using namespace cpp_factory::random_boost;
    testRandom(NormallyDistributedNumber<double>(0,3));
    testRandom(UniformlyDistributedIntNumber<int>(-10, 10));
    testRandom(UniformlyDistributedRealNumber<double>(-10.0, 10.0));
    testRandom(RandomGenerator<boost::normal_distribution<float> >(boost::normal_distribution<float>(0,3)));
    return 0;
}