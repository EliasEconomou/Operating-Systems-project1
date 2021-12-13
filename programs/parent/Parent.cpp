#include <iostream>
#include <sys/wait.h>
#include "../../include/semaphores.h"
#include "../../include/sharedmemory.h"
#include "../../include/Message.h"
#include "../../include/filehandler.h"
using namespace std;

void forkAndExec(int totalLines, int n);

int main(int argc, char** argv)
{
	if (argc != 4)
	{
		cout << "Usage: " << *argv << " filename K N" << endl;
		return 0;
	}

	int semid;
	create_semaphores(&semid, 4, 1212, 0);
	semaphore_v(semid, Shared, 1);

	int shmid, shmemSize = sizeof(Message);
	char* shmem = create_sharedmemory(&shmid, 2121, shmemSize);

	FileHandler fileHandler(argv[1]);
	int totalLines = fileHandler.countLines();

	for (int i = 0; i < atoi(argv[2]); i++)
		forkAndExec(totalLines, atoi(argv[3]));

	Message msg;
	semaphore_v(semid, Start, atoi(argv[2]));

	for (int i = 0; i < atoi(argv[2]) * atoi(argv[3]); i++)
	{
		semaphore_p(semid, Write, 1);
		memcpy(&msg, shmem, shmemSize);
		strcpy(msg.content, fileHandler.getLine(msg.id).c_str());
		memcpy(shmem, &msg, shmemSize);
		semaphore_v(semid, Ready, 1);
	}

	for (int i = 0; i < atoi(argv[2]); i++)
		wait(NULL);

	destroy_semaphores(semid);
	detach_sharedmemory(shmem);
	destroy_sharedmemory(shmid);

	return 0;
}

void forkAndExec(int totalLines, int n)
{
	int pid = fork();
	if (pid == 0)
	{
		char tmp1[10], tmp2[10];
		sprintf(tmp1, "%d", totalLines);
		sprintf(tmp2, "%d", n);
		if (execlp("../child/Child", "Child", tmp1, tmp2, NULL) == -1)
			perror("execlp");
		exit(1);
	}
	else if (pid < 0)
	{
		cerr << "Error in fork";
		exit(1);
	}
}
