#include "tpool.h"
#include <stdbool.h>

static void * worker_func(void *arg) {
	tpool_t *pool = (tpool_t*) arg;
	while(true) {
		pthread_mutex_lock(&pool->mutex);
		while(is_list_empty(&pool->work_queue)) {
			pthread_cond_wait(&pool->has_work, &pool->mutex);
		}
		work_item_t *wi = 
			container_of(remove_list_first(&pool->work_queue), work_item_t, link);
		pthread_mutex_unlock(&pool->mutex);
		wi->func(wi->arg);
		free(wi);
	}
	return NULL;
}


void tp_init(tpool_t *pool, int pool_size) {
	pthread_mutex_init(&pool->mutex, NULL);
	pthread_cond_init(&pool->has_work, NULL);
	
	init_list_head(&pool->work_queue);
	
	pool->threads = (pthread_t*) malloc(sizeof(pthread_t)*pool_size);
	pool->nthreads = pool_size;
	
	for(int i=0; i < pool_size; ++i) {
		pthread_create(pool->threads+i, NULL, worker_func, pool);
	}
}

void tp_submit(tpool_t *pool, func_address func,  void *arg) {
	pthread_mutex_lock(&pool->mutex);
	work_item_t *wi = (work_item_t *) malloc(sizeof(work_item_t));
	
	wi->func = func;
	wi->arg = arg;
	insert_list_last(&pool->work_queue, &wi->link);
	
	pthread_mutex_unlock(&pool->mutex);
	pthread_cond_signal(&pool->has_work);
	
}
