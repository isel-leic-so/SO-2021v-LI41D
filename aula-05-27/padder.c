#include <pthread.h>
#include <limits.h>
#include <assert.h>
#include <stdio.h>

#include "chrono.h"


#define NVALS 20000
#define NPROCESSORS 4

#define NTHREADS NPROCESSORS

int vals[NVALS];

typedef struct {
	int *pstart;
	int *pend;
	long result;
} context_t;


void *worker_func(void *arg) {
	context_t * ctx= (context_t *) arg;

	long sum = 0;
	for(int *curr = ctx->pstart; curr != ctx->pend; curr++) {
		sum += *curr;
	}
	ctx->result = sum;
	return NULL;
}


long seq_adder(int vals[], int nvals) {
	long total=0;
	for(int i=0; i < nvals; ++i)
		total += vals[i];
	return total;
}

long par_adder(int v[], int size) {
	context_t contexts[NTHREADS];
	int *pref = v;
	int range_size = size/NTHREADS;
	
	pthread_t workers[NTHREADS];
	
	for(int i=0; i < NTHREADS; ++i)  {
		context_t *ctx = contexts + i;
		ctx->pstart = pref;
		ctx->pend = (ctx->pstart + range_size) > v+size 
					? v+size
					: ctx->pstart + range_size;
		ctx->result = 0;
		pref += range_size;
		pthread_create(workers+i, NULL, worker_func, ctx);
	}
	
	// wait for all results
	for(int i=0; i < NTHREADS; ++i)  {
		pthread_join(workers[i], NULL);
	}
	
	
	// aggregate partial results
	
	long total_result =0;
	for(int i=0; i < NTHREADS; ++i)  {
		total_result += contexts[i].result;
	}
	
	return total_result;
}

void init_vals(int v[], int size) {
	for(int i=0; i < size; ++i) 
		v[i] = 1;
}

#define NITERATIONS 5

void test(char *name,
		long (*sum_func)(int vals[], int nvals), 
		int vals[], 
		int nvals, 
		long expected) {
	long less_micros= LONG_MAX;
	long res;
	for(int i=0; i < NITERATIONS; ++i) {
		chrono_t chrono = chrono_start();
		res = sum_func(vals, nvals);
		assert(expected == res);
	
		long micros = chrono_micros(chrono);
		
		if (micros < less_micros) 
			less_micros = micros;
	}
	printf("%s give result of %ld in %ld micros.\n", 
			name, res, less_micros);
	
}

int main() {
	init_vals(vals, NVALS);
	
	
	while(1) {
		test("seq", seq_adder, vals, NVALS, NVALS);
	
		test("par", par_adder, vals, NVALS, NVALS);
		putchar('\n');
	}
	 
	return 0;
}

