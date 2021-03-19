#include <stdio.h>
#include <unistd.h>

int main() {
	int pid = getpid();
	
	printf("Hello from process %d\n", pid);
	fflush(stdout);
	printf("press enter to terminate...");
	getchar();
	return 0;
}
