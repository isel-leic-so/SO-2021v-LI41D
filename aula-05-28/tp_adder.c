#include <pthread.h>
#include <limits.h>
#include <assert.h>
#include <stdio.h>

#include "chrono.h"
#include "tpool.h"
#include "cdl.h"


#define NVALS 2000000
#define NPROCESSORS 4


int vals[NVALS];

tpool_t pool;

typedef struct {
	int *pstart;
	int *pend;
	long result;
	cdl_t *cdl;
} context_t;


void worker_func(void *arg) {
	context_t * ctx= (context_t *) arg;

	long sum = 0;
	for(int *curr = ctx->pstart; curr != ctx->pend; curr++) {
		sum += *curr;
	}
	ctx->result = sum;
	cdl_signal(ctx->cdl);
	 
}


long seq_adder(int vals[], int nvals) {
	long total=0;
	for(int i=0; i < nvals; ++i)
		total += vals[i];
	return total;
}

long par_adder(int v[], int size) {
	context_t contexts[NPROCESSORS];
	int *pref = v;
	int range_size = size/NPROCESSORS;
	cdl_t cdl;
	
	cdl_init(&cdl, NPROCESSORS);
	
	
	for(int i=0; i < NPROCESSORS; ++i)  {
		context_t *ctx = contexts + i;
		ctx->pstart = pref;
		ctx->pend = (ctx->pstart + range_size) > v+size 
					? v+size
					: ctx->pstart + range_size;
		ctx->result = 0;
		ctx->cdl = &cdl;
		pref += range_size;
		tp_submit(&pool, worker_func, ctx);
		
	}
	// wait for all results
	
	cdl_wait(&cdl);
	
	// aggregate partial results
	
	long total_result =0;
	for(int i=0; i < NPROCESSORS; ++i)  {
		total_result += contexts[i].result;
	}
	
	return total_result;
}

void init_vals(int v[], int size) {
	for(int i=0; i < size; ++i) 
		v[i] = 1;
}

#define NITERATIONS 10

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

#define NRUNS 10

int main() {
	
	tp_init(&pool, NPROCESSORS);
	
	init_vals(vals, NVALS);
	
	for(int i=0; i < NRUNS; ++i) {
		test("seq", seq_adder, vals, NVALS, NVALS);
		test("par", par_adder, vals, NVALS, NVALS);
		putchar('\n');
	}
	
	 
	return 0;
}

