#include "cdl.h"

void cdl_init(cdl_t *cdl, int initial) {
	cdl->counter = initial;
	pthread_mutex_init(&cdl->mutex, NULL);
	pthread_cond_init(&cdl->completed, NULL);
}

void cdl_signal(cdl_t* cdl) {
	pthread_mutex_lock(&cdl->mutex);
	if (--cdl->counter == 0) {
		// the last one to signal.
		// We have the responsability to awake the countdownlatch waiters 
		pthread_cond_broadcast(&cdl->completed);
	}
	pthread_mutex_unlock(&cdl->mutex);

}


void cdl_wait(cdl_t *cdl) {
	pthread_mutex_lock(&cdl->mutex);
	if (cdl->counter > 0) {
		pthread_cond_wait(&cdl->completed, &cdl->mutex);
		// we must wait to counter be zero
	}
	pthread_mutex_unlock(&cdl->mutex);
}

