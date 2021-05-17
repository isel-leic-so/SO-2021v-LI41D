/////////////////////////////////////////////////////////////////
//
// CCISEL 
// 2007-2020
//
// UThread library:
//   User threads supporting cooperative multithreading.
//
// Authors:
//   Carlos Martins, Jo�o Trindade, Duarte Nunes, Jorge Martins
// 

#pragma once

#include <assert.h>
#include "../include/uthread.h"
#include "../include/list.h"

//
// The data structure representing the layout of a thread's execution context
// when saved in the stack.
typedef struct _UTHREAD_CONTEXT {
	ULONG r15;
	ULONG r14;
	ULONG r13;
	ULONG r12;
	ULONG rbx;
	ULONG rbp;
	void (*ret_addr)();
} UTHREAD_CONTEXT, *PUTHREAD_CONTEXT;


//
// The descriptor of a user thread, containing an intrusive link (through which
// the thread is linked in the ready queue), the thread's starting function and
// argument, the memory block used as the thread's stack and a pointer to the
// saved execution context.
//
typedef struct _UTHREAD {
	PUTHREAD_CONTEXT context;
	LIST_ENTRY       link;
	LIST_ENTRY       alive_link;
	LIST_ENTRY		 join_waiters;
	UT_FUNCTION      function;   
	UT_ARGUMENT      argument; 
	PUCHAR           stack;
} UTHREAD, *PUTHREAD;

//
// The fixed stack size of a user thread.
//
#define STACK_SIZE (8 * 4096)

