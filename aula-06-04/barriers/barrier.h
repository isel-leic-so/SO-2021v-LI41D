#pragma once

#include <pthread.h>

typedef struct barrier {
	int parties;
	int arrived;
	int round;
	
	pthread_mutex_t mutex;
	pthread_cond_t all_arrived;
} barrier_t;



void barrier_init(barrier_t *barrier, int parties);
	 

int barrier_await(barrier_t *barrier);
