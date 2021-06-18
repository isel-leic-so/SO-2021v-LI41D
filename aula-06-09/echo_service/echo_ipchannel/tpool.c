#include "tpool.h"
#include <stdio.h>
#include <stdbool.h>

static void * worker_func(void *arg) {
	tpool_t *pool = (tpool_t*) arg;
	
	
	printf("worker thread start!\n");
	while(true) {
		pthread_mutex_lock(&pool->mutex);
		while(is_list_empty(&pool->work_queue)) {
			pthread_cond_wait(&pool->has_work, &pool->mutex);
			if (pool->in_shutdown)
				printf("worker thread awaked\n");
		}
		work_item_t *wi = 
			container_of(remove_list_first(&pool->work_queue), work_item_t, link);
	   
		pthread_mutex_unlock(&pool->mutex);
		
		if (wi->func != NULL) {
			wi->func(wi->arg);
			free(wi);
		
		}
		else {
			free(wi);
			printf("worker thread informed of termination\n");
			pthread_mutex_lock(&pool->mutex);
			if (--pool->remaining_threads == 0) {
				pool->shutdown_done = true;
				pthread_cond_broadcast(&pool->workers_terminated);
				
			}
			pthread_mutex_unlock(&pool->mutex);
			break;
		}
		
		
	}
	return NULL;
}


 

void tp_init1(tpool_t *pool, int pool_size) {
	
	pthread_attr_t attr;
	
	pthread_attr_init(&attr);
	
	pthread_mutexattr_t mutex_attr;
	pthread_mutexattr_init(&mutex_attr);
	
	pthread_mutexattr_setpshared(&mutex_attr, PTHREAD_PROCESS_SHARED);
	
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	
	pthread_mutex_init(&pool->mutex, &mutex_attr);
	pthread_cond_init(&pool->has_work, NULL);
	pthread_cond_init(&pool->workers_terminated, NULL);
	
	init_list_head(&pool->work_queue);
	
	pool->threads = (pthread_t*) malloc(sizeof(pthread_t)*pool_size);
	pool->nthreads = pool->remaining_threads = pool_size;
	pool->in_shutdown = pool->shutdown_done = false;
	for(int i=0; i < pool_size; ++i) {
		pthread_create(pool->threads+i, &attr, worker_func, pool);
	}
}

void tp_init(tpool_t *pool) {
	tp_init1(pool, 4);
}

void tp_submit(tpool_t *pool, func_address func,  void *arg) {
	pthread_mutex_lock(&pool->mutex);
	
	if (pool->in_shutdown) {
		pthread_mutex_unlock(&pool->mutex);
		return;
	}
	
	work_item_t *wi = (work_item_t *) malloc(sizeof(work_item_t));
	
	wi->func = func;
	wi->arg = arg;
	insert_list_last(&pool->work_queue, &wi->link);
	
	pthread_mutex_unlock(&pool->mutex);
	pthread_cond_signal(&pool->has_work);
	
}

void tp_shutdown(tpool_t *pool) {
	pthread_mutex_lock(&pool->mutex);
	
	if (pool->in_shutdown) {
		pthread_mutex_unlock(&pool->mutex);
		return;
	}
	
	pool->in_shutdown = true;
	// deliver poison pill work item in order to worker thread termination occurrs
	
	for(int i=0; i < pool->nthreads; ++i) {
		work_item_t *wi = malloc(sizeof(work_item_t));
		wi->func = NULL;
		
		insert_list_last(&pool->work_queue, &wi->link);
	}
	// awake all blocked worker threads
	pthread_cond_broadcast(&pool->has_work);
	

	while (!pool->shutdown_done) {
		pthread_cond_wait(&pool->workers_terminated, &pool->mutex);
	}

	pthread_mutex_unlock(&pool->mutex);
	
	// thread created as detached
	/*
	for(int i=0; i < pool->nthreads; ++i) {
		pthread_join(pool->threads[i], NULL);
	}
	* */
	
	
	free(pool->threads);
	pthread_cond_destroy(&pool->has_work);
	pthread_cond_destroy(&pool->workers_terminated);
	pthread_mutex_destroy(&pool->mutex);
	
	
}
