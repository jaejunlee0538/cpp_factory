//
// Created by ub1404 on 15. 9. 9.
//

#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

namespace cpp_factory {
    class PIDController {
    public:
        PIDController(const double &Kp = 0, const double &Ki = 0, const double &Kd = 0,
                      const double &iMax = 0, const double &iMin = 0, const double &cmdMax = 0,
                      const double &cmdMin = 0);

        void reset();

        void resetIErr();

        void init(const double &Kp, const double &Ki, const double &Kd,
                  const double &iMax, const double &iMin, const double &cmdMax,
                  const double &cmdMin);

        /*
     * err  : error value(target - real)
     * dt   : elapsed time(in seconds) from the last update call.
     */
        double update(const double &err, const double &dt);

        /*******************Getters and Setters********************/
        double getKp() const;

        void setKp(double Kp);

        double getKi() const;

        void setKi(double Ki);

        double getKd() const;

        void setKd(double Kd);

        double getIMax() const;

        void setIMax(double iMax);

        double getIMin() const;

        void setIMin(double iMin);

        double getCmdMax() const;

        void setCmdMax(double cmdMax);

        double getCmdMin() const;

        void setCmdMin(double cmdMin);


        double getPErr() const;

        double getIErr() const;

        double getDErr() const;

        double getCmd() const;

    protected:
        /*
     * Gain values for P.I.D
     */
        double Kp, Ki, Kd;

        /*
     * iMax and iMin stand for upper and lower limit of error integration which used
     * when calculating I term in PID. Usally, iMax stands for limit of positive value
     * and iMin stands for limit of negative value.
     * As there is no support for unlimited i-term, you must specify iMax/iMin
     * big enough for your system.
     */
        double iMax, iMin;

        /*
     * cmdMax and cmdMin stand for upper and lower limit of PID's output respectively.
     * Usually, cmdMax stands for limit of positive command and cmdMin
     * stands for limit of negative command.But it's depending on the usage.
     * As there is no support for unlimited command, you must specify cmdMax/cmdMin
     * big enough for your system.
     */
        double cmdMax, cmdMin;

        double pErr, iErr, dErr;
        double cmd;
    };
}

#endif