/**
 * a queue with semaphores sinchronization
 * for empty and full conditions
 * 
 * JM, june 2021
 */

#include <stdio.h>
#include <string.h>
#include "queue.h"


static node_t * node_create(void *msg, int size) {
	node_t *node = malloc(sizeof(node_t)+ size);
	node->msg_size = size;
	memcpy(node->msg, msg, size);
	return node;
}

void queue_init(queue_t *q, int max_size) {
	init_list_head(&q->head);
	sem_init(&q->elem_avaiable, 0, max_size);
	sem_init(&q->space_avaiable, max_size, max_size);
	pthread_mutex_init(&q->mutex, NULL);
}



void queue_put(queue_t *q, void *msg, int size) {
	sem_wait(&q->space_avaiable);
	pthread_mutex_lock(&q->mutex);
	node_t *node = node_create(msg, size);
	insert_list_last(&q->head, &node->link);
	pthread_mutex_unlock(&q->mutex);
	sem_post(&q->elem_avaiable);
}	


int queue_get(queue_t *q, char *msg, int capacity) {
	sem_wait(&q->elem_avaiable);
	pthread_mutex_lock(&q->mutex);
	node_t *node = container_of(remove_list_first(&q->head), node_t, link);
	pthread_mutex_unlock(&q->mutex);
	sem_post(&q->space_avaiable);
	int size = node->msg_size;
	memcpy(msg, node->msg, node->msg_size);
	free(node);
	return size;	
}	
