#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#define MAX_STACK (1024*4)

typedef struct {
	uint64_t *sp;
	uint64_t stack[MAX_STACK];
} UTHREAD, *PUTHREAD;

void context_switch(PUTHREAD curr, PUTHREAD next);

UTHREAD ut1, ut2, main_thread;


void f1() {
	printf("enter uthread ut1\n");
	context_switch(&ut1, &ut2);
	printf("leave uthread ut1\n");
	context_switch(&ut1, &ut2);
	assert(!"Supposed to be here");
}


void f2() {
	printf("enter uthread ut2\n");
	context_switch(&ut2, &ut1);
	printf("leave uthread ut2\n");
	context_switch(&ut2, &main_thread);
	assert(!"Supposed to be here");
}

/**
 * prepare the context for a new thread
 */
void ut_init(PUTHREAD ut, void (*func)()) {
	/*
	 * context:
	 * 	return address
	 *  rbp
	 *  rbx
	 *  r12
	 *  r13
	 *  r14
	 *  r15
	 *   
	 */
	ut->sp = ut->stack + MAX_STACK - 7;
	ut->stack[MAX_STACK-1] = (uint64_t) func;
}


int main() {
	ut_init(&ut1, f1);
	ut_init(&ut2, f2);
	
	printf("start test!\n");
	context_switch(&main_thread, &ut1);
	
	printf("end test!\n");
	return 0;
	
}
