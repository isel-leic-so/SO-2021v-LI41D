#pragma once

#include <pthread.h>
#include "list.h"

typedef void (*func_address)(void *);

typedef struct work_item {
	func_address func;
	void *arg;
	list_entry_t link;
} work_item_t;


typedef struct tpool {
	pthread_t *threads;
	int nthreads;
	list_entry_t work_queue;
	pthread_mutex_t mutex;
	pthread_cond_t has_work;
} tpool_t;


void tp_init(tpool_t *pool, int pool_size);

void tp_submit(tpool_t *pool, func_address func,  void *arg);
