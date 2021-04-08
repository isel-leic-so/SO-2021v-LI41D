#include <stdio.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main() {
	int pid = getpid();
	
	printf("Hello from process %d\n", pid);
	
	int new_fdout = open("out2.txt", O_WRONLY | O_CREAT, 0666);
	if (new_fdout == -1) {
		perror("error creating the new output standard");
		return 1;
	}
	printf("new fd out = %d\n", new_fdout);
	
	dup2(new_fdout, 1);
	
	printf("Hello now to new standard output!\n");
	 
	return 0;
}
