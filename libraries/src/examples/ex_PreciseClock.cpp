#include <stdio.h>
#include <stdlib.h>
#include <cpp_factory/clock/PreciseClock.h>
#include <iostream>

#if defined(WIN32) | defined(WIN64)
#include <conio.h>
#elif defined(__linux__)
#include <cpp_factory/conio_linux.h>
#define _kbhit 			kbhit
#define _getch 			getch
#define Sleep(msec)		usleep(msec*1000)

#endif
using namespace cpp_factory;

void myFunction(){
	ElapsedTime elapsedTime;

	::usleep(1234000);
	std::cerr<<elapsedTime<<std::endl;
}

void myFunction2(){
	//	ElapsedTimeAutoPrinter perf("myFunction", std::cerr);
//	SCOPED_ELAPSED_TIME_WITH_FUNC_NAME(std::cerr);
	SCOPED_ELAPSED_TIME("", std::cerr);
	::usleep(rand()%10000+50000);//50~60ms
}

int main()
{
	{
		std::cerr << "------------Elapsed Time(MACRO)---------" << std::endl;
		myFunction();
	}

	{
		std::cerr<<"--------------ElapsedTime---------------"<<std::endl;
		for(int i=0;i<10;i++){
			myFunction2();
		}

		ElapsedTimePrinter etp("Elapsed Time");
		::usleep(50000);
		std::cerr << etp.getElapsedTimeMessage() << std::endl;
		::usleep(50000);
		std::cerr << etp.getElapsedTimeMessage() << std::endl;
		::usleep(50000);
		std::cerr << etp.getElapsedTimeMessage() << std::endl;

		etp.reset();
		::usleep(50000);
		std::cerr<<etp.getElapsedTimeMessage()<<std::endl;
		::usleep(50000);
		std::cerr<<etp.getElapsedTimeMessage()<<std::endl;
	}

	{
		std::cerr << "------------Timeout---------------------" << std::endl;
		ElapsedTime clock(false);
		ClockTimeout timeout(1.5);
		while (1) {
			if(clock.getElapsedTime_sec()>5.0)
				break;
			if (timeout.isTimeout()) {
				timeout.resetTimeout();
				fprintf(stderr,"\n");
			}
			fprintf(stderr, "%10.3lf\r", clock.getElapsedTime_sec());

		}
	}
	{
		std::cerr << "----------------Frequency Estimation--------------" << std::endl;
		ElapsedTime clock(false);
		FrequencyEstimator freq(1.0);
		while (1) {

			double frequency;
			frequency = freq.update(1);
			Sleep(20);
			fprintf(stderr, "%6.3lf Hz\r", frequency);
			if(clock.getElapsedTime_sec()>5.0)
				break;
		}
	}
	return 0;
}

