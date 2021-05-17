#include "uthreadinternal.h"
#include <stdlib.h>

//
// The currently executing thread.
//


__attribute__((visibility("hidden")))
PUTHREAD running_thread;

UTHREAD main_thread;

LIST_ENTRY ready_queue;

__attribute__((visibility("hidden")))
void   context_switch(PUTHREAD CurrentThread, PUTHREAD NextThread);

__attribute__((visibility("hidden")))
void   internal_exit(PUTHREAD CurrentThread, PUTHREAD NextThread);

static PUTHREAD ut_next_thread();

void ut_init () {
	init_list_head(&ready_queue);
}


void cleanup_thread(PUTHREAD thread) {
	free(thread->stack);
	free(thread);
}


void ut_exit() {
	// to implement
	
	internal_exit(running_thread, ut_next_thread());

}

static void internal_start() {
	running_thread->function(running_thread->argument);
	ut_exit();
}

HANDLE ut_create (UT_FUNCTION function, UT_ARGUMENT argument) {
	
	PUTHREAD newThread = (PUTHREAD) malloc(sizeof(UTHREAD));
	PUCHAR stack = (PUCHAR) malloc(STACK_SIZE);
	
	newThread->stack = stack;
	newThread->function = function;
	newThread->argument = argument;
	
	// create new context
	
	PUTHREAD_CONTEXT context =  (PUTHREAD_CONTEXT) (newThread->stack + STACK_SIZE -sizeof(ULONG))-1;
	context->rbp = 0;
	context->ret_addr = internal_start;
	
	newThread->context = context;
	
	// insert uthread descritor in ready queue
	insert_tail_list(&ready_queue, &newThread->link);
	return newThread;
	
}

static PUTHREAD ut_next_thread() {
	PUTHREAD nextThread;
	
	if (is_list_empty(&ready_queue))
		nextThread = &main_thread;
	else {
		nextThread = container_of(remove_head_list(&ready_queue), UTHREAD, link);
	}
	return nextThread;
}


void schedule() {
	// decide which thread is the next thread
	PUTHREAD nextThread = ut_next_thread();
	context_switch(running_thread, nextThread);
	
}

void ut_yield () {
	if (!is_list_empty(&ready_queue)) {
		insert_tail_list(&ready_queue, &running_thread->link);
		schedule();
	}
}

HANDLE ut_self () {
	return (HANDLE) running_thread;
}

void ut_run() {
	running_thread = &main_thread;
	schedule();
}


void ut_end() {
	// nothing to do for now
}
