#include <pthread.h>
#include <stdio.h>

#define NVALS 20000000
#define NPROCESSORS 2

#define NTHREADS NPROCESSORS

int vals[NVALS];

typedef struct {
	int *pstart;
	int *pend;
	long result;
} context_t;


void *worker_func(void *arg) {
	context_t * ctx= (context_t *) arg;
	ctx->result = 0;
	for(int *curr = ctx->pstart; curr != ctx->pend; curr++) {
		ctx->result += *curr;
	}
	return NULL;
}


long padder(int v[], int size) {
	context_t contexts[NTHREADS];
	int *pref = v;
	int range_size = size/NTHREADS;
	
	pthread_t workers[NTHREADS];
	
	for(int i=0; i < NTHREADS; ++i)  {
		context_t *ctx = contexts + i;
		ctx->pstart = pref;
		ctx->pend = ctx->pstart + range_size;
		ctx->result = 0;
		pref += range_size;
		pthread_create(workers+i, NULL, worker_func, ctx);
	}
	for(int i=0; i < NTHREADS; ++i)  {
		pthread_join(workers[i], NULL);
	}
	
	long total_result =0;
	// aggregate partial results
	for(int i=0; i < NTHREADS; ++i)  {
		total_result += contexts[i].result;
	}
	
	return total_result;
}

void init_vals(int v[], int size) {
	for(int i=0; i < size; ++i) 
		v[i] = 1;
}

int main() {
	init_vals(vals, NVALS);
	long total = padder(vals, NVALS);
	printf("vals sum=%ld\n", total);
	return 0;
}


