// Test for join operation

#include <stdio.h>
#include "../include/uthread.h"

HANDLE joined_thread;

void joiner(UT_ARGUMENT arg) {
	const char *id = arg;
	printf("Start joiner %s\n", id);
	
	ut_join(joined_thread);

 
	printf("End joiner %s\n", id);

}

void joined(UT_ARGUMENT arg) {
	printf("joined thread start\n");
	ut_yield();
	printf("joined thread end\n");
}


void join_test() {
	printf("\n :: Test 2 - BEGIN :: \n\n");
	
	ut_create(joiner, "1");
	ut_create(joiner, "2");
	joined_thread = ut_create(joined, NULL);
	ut_run();
	printf("\n\n :: Test 2 - END :: \n");
}



int main () {
	ut_init();
 
	join_test();
	 
	ut_end();
	return 0;
}
