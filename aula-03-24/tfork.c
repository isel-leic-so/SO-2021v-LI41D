#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
	int val = 10;
	int npid;
	
	int wait_child = 1;
	
	if (argc > 1) 
		wait_child = 0;
	
	printf("parent process =%d\n", getpid());
	
	if ((npid = fork()) == 0) {
		
		printf("child: my process id is %d, val=%d\n", getpid(), val);
		val = 25;
		
		sleep(10);
		exit(0);
		
	}
	else if (npid  == -1) {
		perror("error creating child!");
		exit(2);
	}
	
	if (wait_child == 1) {
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
	
	printf("press retiurn to terminate...");
	getchar();
	return 0;
}
	
	
