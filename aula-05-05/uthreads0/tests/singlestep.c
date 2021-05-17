
// Test to run in single step

 
#include <stdio.h>
#include "../include/uthread.h"

void func1(UT_ARGUMENT arg) {

	printf("Start func1\n");
	
	ut_yield();

 
	printf("End func1\n");

}

void func2(UT_ARGUMENT arg) {
	printf("func2\n");
}

void test2() {
	printf("\n :: Test 2 - BEGIN :: \n\n");
	
	ut_create(func1, NULL);
	ut_create(func2, NULL);
	ut_run();
	printf("\n\n :: Test 2 - END :: \n");
}



int main () {
	ut_init();
 
	test2();
	 
	ut_end();
	return 0;
}

