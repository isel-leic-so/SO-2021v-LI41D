#include <pthread.h>


#include <stdio.h>
#include "chrono.h"

#define MAX_THREADS 5000


void * func(void *arg) {
	return NULL;
}


int main() {
	pthread_t threads[MAX_THREADS];
	chrono_t chrono = chrono_start();
	for(int i=0; i < MAX_THREADS; ++i) {
		if (pthread_create(threads+i, NULL, func, NULL) != 0) {
			perror("error creating thread");
			return 1;
		}
	}
	
	long duration = chrono_micros(chrono);
	
	
	for(int i=0; i < MAX_THREADS; ++i) {
		pthread_join(threads[i], NULL);
	}
	
	printf("passed %ld micros for %d threads\n", duration, MAX_THREADS);
	printf("create/join thread in %ld micros\n", duration/MAX_THREADS);
	return 0;
	
}
