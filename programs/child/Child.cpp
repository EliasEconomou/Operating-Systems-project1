#include <iostream>
#include "../../include/semaphores.h"
#include "../../include/sharedmemory.h"
#include "../../include/Message.h"

using namespace std;

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		cout << "Usage: " << *argv << " totalLines N" << endl;
		return 0;
	}
	else
		srand(getpid());

	int semid;
	access_semaphores(&semid, 4, 1212);

	int shmid, shmemSize = sizeof(Message);
	char* shmem = access_sharedmemory(&shmid, 2121, shmemSize);

	double average = 0.0;

	semaphore_p(semid, Start, 1);
	cout << "Child (" << getpid() << ") is starting" << endl;

	Timer timer;
	for (int i = 0; i < atoi(argv[2]); i++)
	{
		Message msg;
		bzero(&msg, shmemSize);
		msg.id = 1 + rand() % atoi(argv[1]);
		timer.begin();
		semaphore_p(semid, Shared, 1);
		memcpy(shmem, &msg, shmemSize);
		semaphore_v(semid, Write, 1);
		semaphore_p(semid, Ready, 1);
		memcpy(&msg, shmem, shmemSize);
		semaphore_v(semid, Shared, 1);
		cout << "Child (" << getpid() << ") req: " << msg.id << ", resp: " << msg.content << endl;
		timer.end();
		average = average + timer.timeDiff();
	}

	detach_sharedmemory(shmem);
	cout << "Child (" << getpid() << "): Average waiting time is " << average/atoi(argv[2]) << endl;
	return 0;
}
