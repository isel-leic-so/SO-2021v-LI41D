#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

void sigchld(int sig) {
	int pid = waitpid(-1, NULL, 0);
	printf("child process %d terminated!\n", pid);
}

void sigint(int sig) {
	printf("sigint received!\n");
}

int main(int argc, char *argv[]) {
	int val = 10;
	int npid;
	
	//signal(SIGCHLD, sigchld);
	signal(SIGINT, sigint);
	
	int wait_child = 1;
	
	if (argc > 1) 
		wait_child = 0;
	
	printf("parent process =%d\n", getpid());
	
	if ((npid = fork()) == 0) {
		
		printf("child: my process id is %d, val=%d\n", getpid(), val);
		val = 25;
		
		sleep(10);
		printf("child process terminate now!");
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
#ifdef TERMINATE_WITH_INPUT
	printf("press return to terminate...");
	getchar();
#else
	printf("wait 60 seconds to terminate..");
	sleep(60);
#endif
	return 0;
}
	
	
