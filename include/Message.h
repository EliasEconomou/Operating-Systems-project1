#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <sys/time.h>
#define SIZE 101

struct Message
{
	int id;
	char content[SIZE];
};

class Timer
{
	struct timeval start;
	double elapsedTime;
public:
	Timer() { elapsedTime = 0.0; }
	void begin() { gettimeofday(&start, NULL); }
	void end()
	{
		struct timeval stop;
		gettimeofday(&stop, NULL);
		elapsedTime = (stop.tv_sec - start.tv_sec) * 1000.0 + (stop.tv_usec - start.tv_usec) / 1000.0;
	}
	double timeDiff() { return elapsedTime; }

};

#endif /* MESSAGE_H_ */
