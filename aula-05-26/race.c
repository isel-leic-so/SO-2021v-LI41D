#include <pthread.h>
#include <stdio.h>

volatile long result;

pthread_mutex_t mutex;

#define MAX_THREADS 10

#define NITERATIONS 10000000

void *pthread_func(void *arg) {
	for(int i=0; i < NITERATIONS; ++i) {
		pthread_mutex_lock(&mutex);
		int temp = result;
		temp = temp+1;
		result = temp;
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

int main() {
	pthread_t pthreads[MAX_THREADS];
	
	pthread_mutex_init(&mutex, NULL);
	
	for(int i=0; i < MAX_THREADS; ++i)
		pthread_create(pthreads+i, NULL, pthread_func, NULL);
		
	
	for(int i=0; i < MAX_THREADS; ++i)
		pthread_join(pthreads[i], NULL);
	
	printf("result = %ld\n", result);
	return 0;
}
	
