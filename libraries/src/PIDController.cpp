//
// Created by ub1404 on 15. 9. 9.
//

#include "cpp_factory/PIDController.h"
#include "cpp_factory/MathUtils.h"


namespace cpp_factory {
    PIDController::PIDController(const double &Kp, const double &Ki, const double &Kd,
                                 const double &iMax, const double &iMin, const double &cmdMax,
                                 const double &cmdMin) {
        this->Kp = Kp;
        this->Ki = Ki;
        this->Kd = Kd;
        this->iMax = iMax;
        this->iMin = iMin;
        this->cmdMax = cmdMax;
        this->cmdMin = cmdMin;
        this->reset();
    }

    void PIDController::reset() {
        pErr = 0.0;
        iErr = 0.0;
        dErr = 0.0;
        cmd = 0.0;
    }

    void PIDController::resetIErr() {
        iErr = 0.0;
    }

    void PIDController::init(const double &Kp, const double &Ki, const double &Kd,
                             const double &iMax, const double &iMin, const double &cmdMax,
                             const double &cmdMin) {
        this->Kp = Kp;
        this->Ki = Ki;
        this->Kd = Kd;
        this->iMax = iMax;
        this->iMin = iMin;
        this->cmdMax = cmdMax;
        this->cmdMin = cmdMin;
    }

/*
 * err  : error value(target - real)
 * dt   : elapsed time(in seconds) from the last update call.
 */
    double PIDController::update(const double &err, const double &dt) {
        if (isAlmostEqual(dt, 0.0) || isNan(err)) {
            //unacceptable inputs.
            return cmd;
        }

        dErr = (err - pErr) / dt;
        pErr = err; //TODO : Applying low-pass filter when calculating D term.
        iErr = iErr + pErr * dt;

        if (iErr > iMax)
            iErr = iMax;
        if (iErr < iMin)
            iErr = iMin;

        //Compute temporary command
        cmd = Kp * pErr + Kd * dErr + Ki * iErr;

        //Command Saturation
        if (cmd > cmdMax)
            cmd = cmdMax;

        if (cmd < cmdMin)
            cmd = cmdMin;

        return cmd;
    }

/*******************Getters and Setters********************/
    double PIDController::getKp() const {
        return Kp;
    }

    void PIDController::setKp(double Kp) {
        this->Kp = Kp;
    }

    double PIDController::getKi() const {
        return Ki;
    }

    void PIDController::setKi(double Ki) {
        this->Ki = Ki;
    }

    double PIDController::getKd() const {
        return Kd;
    }

    void PIDController::setKd(double Kd) {
        this->Kd = Kd;
    }

    double PIDController::getIMax() const {
        return iMax;
    }

    void PIDController::setIMax(double iMax) {
        this->iMax = iMax;
    }

    double PIDController::getIMin() const {
        return iMin;
    }

    void PIDController::setIMin(double iMin) {
        this->iMin = iMin;
    }

    double PIDController::getCmdMax() const {
        return cmdMax;
    }

    void PIDController::setCmdMax(double cmdMax) {
        this->cmdMax = cmdMax;
    }

    double PIDController::getCmdMin() const {
        return cmdMin;
    }

    void PIDController::setCmdMin(double cmdMin) {
        this->cmdMin = cmdMin;
    }


    double PIDController::getPErr() const {
        return pErr;
    }

    double PIDController::getIErr() const {
        return iErr;
    }

    double PIDController::getDErr() const {
        return dErr;
    }

    double PIDController::getCmd() const {
        return cmd;
    }
}