//
// Created by ub1404 on 16. 3. 29.
//

#ifndef CPP_FACTORY_MATHUTILS_H
#define CPP_FACTORY_MATHUTILS_H

#include <math.h>
#include <limits>

namespace cpp_factory {
    template<typename T>
    inline bool isAlmostEqual(const T a, const T &b) {
        double diff = fabs(a - b);
        if (diff < std::numeric_limits<double>::min())
            return true;
        if (diff < std::numeric_limits<double>::epsilon() * fabs(a + b) * 2)
            return true;
        return false;
    }

    inline bool isNan(const double &a) {
        return a != a;
    }
}
#endif //CPP_FACTORY_MATHUTILS_H
