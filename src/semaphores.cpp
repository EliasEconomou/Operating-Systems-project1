#include <stdio.h>
#include <stdlib.h>

#include "../include/semaphores.h"
#include "../include/semun.h"

int semaphore_p(int sem_id, int sem_number, int val)
{
	struct sembuf sem_b;
	sem_b.sem_num = sem_number;
	sem_b.sem_op = -val;
	sem_b.sem_flg = 0;
	if (semop(sem_id, &sem_b, 1) == -1) {
		fprintf(stderr, "semaphore_p failed\n");
		return(0);
	}
	return(1);
}

int semaphore_v(int sem_id, int sem_number, int val)
{
	struct sembuf sem_b;
	sem_b.sem_num = sem_number;
	sem_b.sem_op = val; /* V() */
	sem_b.sem_flg = 0;
	if (semop(sem_id, &sem_b, 1) == -1) {
		fprintf(stderr, "semaphore_v failed\n");
		return(0);
	}
	return(1);
}

void create_semaphores(int* sem_id, int sem_number, int key_id, int val)
{
	if (((*sem_id) = semget(SEMKEY+(key_id*10), sem_number, 0600 | IPC_CREAT)) < 0)
	{
		fprintf(stderr, "create semaphores failed");
		exit(0);
	} /* Create semaphore set*/
	fprintf(stdout, "Created semaphore with identifier %d\n", *sem_id);
	int i;
	union semun arg;
	arg.val = val;
	for (i = 0; i < sem_number; i++)
	{
		if (semctl(*sem_id, i, SETVAL, arg) < 0)
		{
			fprintf(stderr, "create semaphores failed");
			exit(0);
		} /* Initialize semaphores for locking */
	}
}

void destroy_semaphores(int sem_id)
{
	if (semctl(sem_id, 0, IPC_RMID, 0) < 0)
	{
		fprintf(stderr, "destroy semaphores failed");
		exit(1);
	}
	fprintf(stdout, "Destroyed semaphore with identifier %d\n", sem_id);
}

void access_semaphores(int* sem_id, int sem_number, int key_id)
{
	if ((*sem_id = semget(SEMKEY+(key_id*10), sem_number, 0600)) < 0)
	{
		fprintf(stderr, "access semaphores failed");
		exit(0);
	} /* Access semaphore set*/
	fprintf(stdout, "Accessed semaphore with identifier %d\n", *sem_id);
}
