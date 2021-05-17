#include <stdio.h>
#include <stdint.h>

#define MAX_STACK (1024*4)

typedef struct {
	uint64_t *sp;
	uint64_t stack[MAX_STACK];
} UTHREAD, *PUTHREAD;

void context_switch(PUTHREAD curr, PUTHREAD next);

UTHREAD ut1, ut2, dummy;


void f1() {
	printf("enter uthread ut1\n");
	context_switch(&ut1, &ut2);
	printf("leave uthread ut1\n");
	context_switch(&ut1, &ut2);
}


void f2() {
	printf("enter uthread ut2\n");
	context_switch(&ut2, &ut1);
	printf("leave uthread ut2\n");
	context_switch(&ut2, &dummy);
	
}

void ut_init(PUTHREAD ut, void (*func)()) {
	ut->sp = ut->stack + MAX_STACK - 7;
	ut->stack[MAX_STACK-1] = (uint64_t) func;
}


int main() {
	ut_init(&ut1, f1);
	ut_init(&ut2, f2);
	
	printf("start test!\n");
	context_switch(&dummy, &ut1);
	
	printf("end test!\n");
	return 0;
	
}
