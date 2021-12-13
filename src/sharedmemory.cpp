#include "../include/sharedmemory.h"

char* create_sharedmemory(int* shm_id, int key_id, int size)
{
	if ((*shm_id = shmget(SHMKEY+key_id, size, 0600 | IPC_CREAT)) < 0)
	{
		fprintf(stderr, "create shared memory failed");
		return NULL;
	} /* Create shared memory */
	fprintf(stdout, "Created shared memory region with identifier %d\n", *shm_id);
	char *shmem = (char*)shmat(*shm_id, (char *) 0, 0);
	bzero(shmem, size);
	return shmem;
}

char* access_sharedmemory(int* shm_id, int key_id, int size)
{
	if ((*shm_id = shmget(SHMKEY+key_id, size, 0600)) < 0)
	{
		fprintf(stderr, "access shared memory failed");
		return NULL;
	} /* Create shared memory */
	fprintf(stdout, "Accessed shared memory region with identifier %d\n", *shm_id);
	char *shmem = (char*)shmat(*shm_id, (char *) 0, 0);
	return shmem;
}

void detach_sharedmemory(char* shmem)
{
	shmdt(shmem);
}

void destroy_sharedmemory(int shm_id)
{
	if (shmctl(shm_id, IPC_RMID, (struct shmid_ds *) 0) < 0)
	{
		fprintf(stderr, "destroy shared memory failed");
		exit(0);
	} /* Destroy shared memory */
	fprintf(stdout, "Removed shared memory region with identifier %d\n", shm_id);
}
