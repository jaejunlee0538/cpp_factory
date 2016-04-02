//
// Created by ub1404 on 16. 3. 25.
//

#ifndef VELODYNE_SLAM_CYCLE_DETECTOR_H
#define VELODYNE_SLAM_CYCLE_DETECTOR_H
#include <assert.h>
template <typename T>
class CycleDetect{
public:
    /*
     * min_v : minimum possible value
     * max_v : maximum possible value
     * direction : 1 or -1. The direction must be pre-determined.
     *  The value must increase/decrease monotonically.
     */
    CycleDetect(T min_v, T max_v, int direction)
    {
        this->set(min_v, max_v, direction);
    }

    void set(T min_v, T max_v, int direction){
        assert(max_v > min_v);
        assert(direction == 1 || direction == -1);

        this->min_v = min_v;
        this->max_v = max_v;
        this->dir = direction;
        magnitude = max_v - min_v;

        this->reset();
    }

    void reset(){
        n_cycles = 0;
        accum = 0;
        first_run = true;
    }

    int update(T v){
        assert(v < max_v);
        assert(v > min_v);

        if(first_run){
            first_run = false;
            v_prev = v;
        }

        T diff = v - v_prev;

        if(diff*dir < 0){
            diff += dir*magnitude;
        }
        accum += diff;

        v_prev = v;

        if(std::abs(accum) >= magnitude){
            accum = accum - dir*magnitude;
            n_cycles++;
            return 1;
        }
        return 0;
    }

    unsigned int getNumCycles() const{return n_cycles;}
protected:
    unsigned int n_cycles;
    T min_v, max_v;
    T magnitude;
    T accum;
    T v_prev;
    bool first_run;
    int dir;
};
#endif //VELODYNE_SLAM_CYCLE_DETECTOR_H
