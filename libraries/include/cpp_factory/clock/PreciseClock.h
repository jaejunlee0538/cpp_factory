#ifndef PRECISE_CLOCK_H_
#define PRECISE_CLOCK_H_
/*
made by jaejunlee, 2015.10.23
*/
#include <iostream>
#include <iomanip>
#include <sstream>

namespace cpp_factory {
	/*********************************************************************************/
	class PreciseClock {
	public:
		PreciseClock();

		virtual ~PreciseClock() { };
	public:

		/*
		 * Return current time in seconds.
		 *  Be warn that retrieved time stamp might not be
		 *  an absolute time stamp(i.e. time stamp from the Epoch).
		 *  Rather than an absolute time stamp, a time stamp having
		 *  high short-term precision is used.
		 */
		double getPreciseTime(void) const;

	private:

#if defined(WIN32) | defined(WIN64)
private:
	double freq_coeff;
#elif defined(__linux__)

#endif
	};

	/*********************************************************************************/
	/*
	 * Usage :
	 * 	ElapsedTime elapsed_time(true);
	 * 	//Do something....
	 * 	std::cerr<<elapsed_time<<" sec"<<std::endl;
	 * 	//Do something...
	 * 	std::cerr<<elapsed_time<<" sec"<<std::endl;
	 *	//Do something...
	 *	std::cerr<<elapsed_time.getElapsedTime()<<" sec"<<std::endl;
	 *
	 *
	 *
	 */
	class ElapsedTime: protected PreciseClock{
	public:
		/*
		 * auto_reset : if it is true, 'reset' method is called
		 * when 'getElapsedTime_sec' method is called.
		 */
		ElapsedTime(bool auto_reset=true):auto_reset(auto_reset){
			this->reset();
		}

		/*
		 * Update current time and set start time(t_start) same with current time.
		 */
		void reset(void) {
			this->t_current = this->getPreciseTime();
			this->t_start = this->t_current;
		}

		/*
		 * Return elapsed time from t_start in seconds.
		 */
		double getElapsedTime_sec(void){
			this->t_current = this->getPreciseTime();
			double t_elapsed = this->t_current - this->t_start;
			if(auto_reset)
				this->t_start = this->t_current;
			return t_elapsed;
		}

	protected:
		double t_start, t_current; //To increase accuracy, think changing this to long long.
	private:
		bool auto_reset;
	};

	std::ostream& operator<<(std::ostream& os, ElapsedTime& et);

	/*********************************************************************************/
	class ElapsedTimePrinter : protected ElapsedTime {
	public:
		ElapsedTimePrinter(bool auto_reset=false, const std::string &message = "")
				: msg(message) ,ElapsedTime(auto_reset){
			if (msg.empty())
				msg_empty = true;
		}

		void reset(void) {
			ElapsedTime::reset();
		}

		std::string getElapsedTimeMessage(){
			std::ostringstream oss;
			if(msg_empty)
				oss<<std::setprecision(6) << getElapsedTime_sec();
			else
				oss << msg << " : " << std::setprecision(6) << getElapsedTime_sec();
			return oss.str();
		}

	protected:
		std::string msg;
		bool msg_empty;
	};

	/*
	 * When an instance is destructed, it outputs elapsed time from it's construction
	 * to std::ostream& object.
	 * It can be used to estimate running time of a function.
	 */
	class ElapsedTimeAutoPrinter : protected ElapsedTimePrinter {
	public:
		ElapsedTimeAutoPrinter(const std::string &message = "", std::ostream &_os = std::cout)
				: ElapsedTimePrinter(false, message), os(_os) {

		}

		~ElapsedTimeAutoPrinter() {
			os <<getElapsedTimeMessage()<<std::endl;
		}

	protected:
		std::ostream &os;
	};

#define SCOPED_ELAPSED_TIME(msg, stream)			ElapsedTimeAutoPrinter __func_elapsed__(msg, stream)
#define SCOPED_ELAPSED_TIME_WITH_FUNC_NAME(stream)	ElapsedTimeAutoPrinter __func_elapsed__(__PRETTY_FUNCTION__, stream)

	/*********************************************************************************/
	class ClockTimeout : protected ElapsedTime {
	public:

		ClockTimeout(const double &timeout_sec = 0.0);

		virtual ~ClockTimeout();

		void resetTimeout(bool precision_offset = true);

		inline double getTimeoutDuration(void) const { return this->duration_sec; }

		void setTimeoutDuration(const double &timeout_sec);

		bool isTimeout(void);

		double getElapsedFromStart_sec(void);

		double getElapsedFromTimeout_sec(void);

	protected:
		double duration_sec;
		bool is_timeout;
	};

	/*********************************************************************************/
	class FrequencyEstimator {
	public:
		FrequencyEstimator(const double &sampling_period = 0.5);

		virtual ~FrequencyEstimator();

		double update(const unsigned int &count = 1);

		inline void setSamplingPeriod(const double &sampling_period) { sampler.setTimeoutDuration(sampling_period); }

		inline double getSamplingPeriod(void) const { return sampler.getTimeoutDuration(); }

		inline double getFrequency() const { return this->frequency; }

	protected:
		ClockTimeout sampler;
		int event_count;
		double frequency;
	};
	/*********************************************************************************/
}

#endif

