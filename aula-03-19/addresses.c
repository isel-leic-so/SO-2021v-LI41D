#include <stdio.h>

int global=3;

int main() {
	int local;
	
	printf("start...");
	getchar();
	
	printf("addr(glob_int)=%p, val(global)=%d\n", &global, global);
	printf("addr(local)=%p\n", &local);
	printf("addr(main)=%p...", main);
	
	 
	getchar();
	
	printf("before global change, val(global)=%d...", global);
	getchar();
	global = 4;
	printf("after global change, val(global)=%d...", global);
	getchar();
	
	return 0;
}
