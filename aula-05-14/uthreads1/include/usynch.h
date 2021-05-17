#pragma once

#include "list.h"

// event primitives

typedef struct {
	LIST_ENTRY waiters;
	BOOL signaled;
	
} EVENT;


void event_init(EVENT *event, BOOL initial_state);


void event_wait(EVENT *event);


void event_set(EVENT *event);

void event_clear(EVENT *event);

