#ifndef SHAREDMEMORY_H_
#define SHAREDMEMORY_H_

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/shm.h>

#define SHMKEY 6666

char* create_sharedmemory(int* shm_id, int key_id, int size);
char* access_sharedmemory(int* shm_id, int key_id, int size);
void detach_sharedmemory(char* shmem);
void destroy_sharedmemory(int shm_id);


#endif
