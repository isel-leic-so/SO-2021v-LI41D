#include "../include/usynch.h"
#include "../include/uthread.h"


typedef struct {
	LIST_ENTRY link;
	HANDLE thread;
} WAIT_BLOCK;

void init_wait_block(WAIT_BLOCK * wb) {
	wb->thread = ut_self();
}

void event_init(EVENT *event, BOOL initial_state) {
	init_list_head(&event->waiters);
	event->signaled = initial_state;
}


void event_wait(EVENT *event) {
	if (event->signaled) return;
	WAIT_BLOCK wb;
	
	init_wait_block(&wb);
	
	insert_tail_list(&event->waiters, &wb.link);
	ut_deactivate();
}


void event_set(EVENT *event) {
	event->signaled = TRUE;
	while(!is_list_empty(&event->waiters)) {
		WAIT_BLOCK *wb = container_of(remove_head_list(&event->waiters), WAIT_BLOCK, link);
		ut_activate(wb->thread);
	} 
	
}

void event_clear(EVENT *event) {
	event->signaled = FALSE;
}
