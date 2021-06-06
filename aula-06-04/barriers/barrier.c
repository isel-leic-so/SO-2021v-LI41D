#include "barrier.h"
#include <stdio.h>


void barrier_init(barrier_t *barrier, int parties) {
	
	pthread_mutex_init(&barrier->mutex, NULL);
	pthread_cond_init(&barrier->all_arrived, NULL);
	barrier->parties = parties;
	barrier->arrived = 0;
	barrier->round = 0;
}



int barrier_await(barrier_t *barrier) {
	pthread_mutex_lock(&barrier->mutex);
	
	int index = ++barrier->arrived;
	int r = barrier->round;
	
	if (index == barrier->parties) {
		pthread_cond_broadcast(&barrier->all_arrived);
		barrier->arrived = 0;
		barrier->round++;
	}
	else {
		do {
			pthread_cond_wait(&barrier->all_arrived, &barrier->mutex);
			
		}
		while(barrier->round == r);
		//printf("awaked thread, old round=%d, new round=%d\n", r, barrier->round);
	}
	
	pthread_mutex_unlock(&barrier->mutex);
	
	return (index == barrier->parties) ? PTHREAD_BARRIER_SERIAL_THREAD : 0;
	
}
