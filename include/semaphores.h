#ifndef SEMAPHORES_H
#define SEMAPHORES_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/sem.h>

#define SEMKEY 1144
#define LOCKED   0
#define UNLOCKED 1

#define NUMBER_OF_SEMAPHORES 4
#define Start	    		 0
#define Shared			  	 1
#define	Ready		 		 2
#define	Write		 		 3

void create_semaphores(int* sem_id, int sem_number, int key_id, int val);
void access_semaphores(int* sem_id, int sem_number, int key_id);
int semaphore_p(int sem_id, int sem_number, int);
int semaphore_v(int sem_id, int sem_number, int);
void destroy_semaphores(int sem_id);

#endif
