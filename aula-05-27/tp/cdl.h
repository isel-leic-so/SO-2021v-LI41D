#pragma once

#include <pthread.h>

typedef struct cdl {
	int counter;
	pthread_mutex_t mutex;
	pthread_cond_t completed;
} cdl_t;

void cdl_init(cdl_t *cdl, int initial);

void cdl_signal(cdl_t* cdl);
	
void cdl_wait(cdl_t *cdl);





	
