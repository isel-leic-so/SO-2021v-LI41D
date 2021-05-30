/////////////////////////////////////////////
//
// CCISEL 
// 2007-2019
//
// UThread    Library First    Test
//
// Jorge Martins, 2019..2021
////////////////////////////////////////////

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/uthread.h"



#define DEBUG

#define MAX_THREADS 10



///////////////////////////////////////////////////////////////
//															 //
// Test 1: N threads, each one printing its number M times //
//															 //
///////////////////////////////////////////////////////////////

ULONG test1_count;


void test1_thread (UT_ARGUMENT argument) {
	UCHAR c;
	ULONG index;
	c = (UCHAR) (ULONG) argument;	
	 
	for (index = 0; index < 100; ++index) {
	    putchar(c); fflush(stdout);
		 
	    if ((rand() % 4) == 0) {
			usleep(100000); 
		    //ut_yield();
	    }	 
    }
	++test1_count;
}

void test1 ()  {
	ULONG index;

	test1_count = 0; 

	printf("\n :: Test 1 - BEGIN :: \n\n");

	for (index = 0; index < MAX_THREADS; ++index) {
		ut_create(test1_thread, (UT_ARGUMENT) ('0' + index));
	}   

	ut_run();

	_ASSERTE(test1_count == MAX_THREADS);
	printf("\n\n :: Test 1 - END :: \n");
}


int main () {
	ut_init();
 
	test1();
	 
	ut_end();
	return 0;
}


