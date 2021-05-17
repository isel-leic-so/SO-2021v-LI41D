#include "../include/usynch.h"
#include "../include/uthread.h"


typedef struct {
	LIST_ENTRY link;
	HANDLE thread;
} WAIT_BLOCK;

void initi_wait_block(WAIT_BLOCK * wb, HANDLE thread) {
	wb->thread = thread;
}

void event_init(EVENT *event, BOOL initial_state) {
	init_list_head(&event->waiters);
	event->signaled = initial_state;
}


void event_wait(EVENT *event) {
	if (event->signaled) return;
	WAIT_BLOCK wb;
	
	init_wait_block(&wb, ut_self());
	
	insert_tail_list(&event->waiters, &wb->link);
	ut_deactivate();
	
	
}


void event_set(EVENT *event);

void event_clear(EVENT *event);
