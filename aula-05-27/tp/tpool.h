#ifndef _TPOOL_H
#define _TPOOL_H

#include <pthread.h>

#include "queue.h"
#include <stdbool.h>

#define NTHREADS 4

typedef void (*func_t)(void *arg);

typedef struct {
	func_t func;
	void *arg;
} workitem_t;

typedef struct {
	pthread_t threads[NTHREADS];
	queue_t queue;
} tpool_t;



void tp_init(tpool_t *pool);

void tp_submit(tpool_t *pool, func_t func, void *arg);
	 



#endif
