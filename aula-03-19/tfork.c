#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main() {
	int val = 10;
	int npid;
	
	printf("parent process =%d\n", getpid());
	
	if ((npid = fork()) == 0) {
		val = 25;
		
		printf("child: my process id is %d, val=%d\n", getpid(), val);
		sleep(5);
		exit(0);
		
	}
	else if (npid  == -1) {
		perror("error creating child!");
		exit(2);
	}
	
	int status;
	
	if (waitpid(npid, &status, 0) == -1) {
		perror("error waiting for child termination");
		exit(3);
	}
	
	if (WIFEXITED(status)) 
		printf("child returned %d\n", WEXITSTATUS(status));
	else
		printf("child bad termination!\n");
		
	printf("val=%d\n", val);
	printf("child process id = %d\n", npid);
	
	
	return 0;
}
	
	
