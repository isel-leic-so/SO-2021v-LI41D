#pragma once

#include "list.h"
#include <semaphore.h>
#include <pthread.h>

typedef struct queue {
	list_entry_t head;
	pthread_mutex_t mutex;
	sem_t elem_avaiable;
	sem_t space_avaiable;
} queue_t;


typedef struct node {
	list_entry_t link;
	int msg_size;
	char msg[1];
} node_t;


void queue_init(queue_t *q, int max_size);
	 

void queue_put(queue_t *q, void *msg, int size);
	 

int queue_get(queue_t *q, char *msg, int capacity);
	 
