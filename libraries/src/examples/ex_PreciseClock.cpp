#include <stdio.h>
#include <cpp_factory/PreciseClock.h>

#if defined(WIN32) | defined(WIN64)
#include <conio.h>
#elif defined(__linux__)
#include <cpp_factory/conio_linux.h>
#define _kbhit 			kbhit
#define _getch 			getch
#define Sleep(msec)		usleep(msec*1000)
#endif

using namespace cpp_factory;

int main()
{

	PreciseClock clock;
	ClockTimeout timeout(1.5);

	while(1)
	{
		if(_kbhit())
		{
			int c = _getch();
			if(c == 'q')
			{
				break;
			}
			if(c == 'r')
			{
				clock.reset();
			}
		}
		if(timeout.isTimeout())
		{
			timeout.resetTimeout();
			printf("\n");
		}

		printf("%10.3lf\r", clock.getElapsedTime_sec()); 
		fflush(stdout);
	}
	printf("\n\n\n");
	FrequencyEstimator freq(1.0);
	while(1)
	{
		if(_kbhit())
		{
			int c = _getch();
			if(c == 'q')
			{
				break;
			}
		}
		double frequency;
		frequency = freq.update(1);
		Sleep(20);
		printf("%6.3lf\r", frequency);
		fflush(stdout);
	}
    return 0;
}

