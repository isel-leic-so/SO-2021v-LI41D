#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>



int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("usage: texec <prog> <args...>\n");
		return 1;
	}
	
	int pid_child;
	
	if ( (pid_child = fork()) == -1) {
		//fork error
		perror("error creating child peoc");
		return 2;
	}
	else if (pid_child == 0) {
		// processo filho
		execvp(argv[1], &argv[1]);
		char msg[200];
		
		sprintf(msg, "error loading %s", argv[1]);
		perror(msg);
		exit(1);	
	}
	else {
		// parent process
		waitpid(pid_child, NULL, 0);
	}
	
	printf("\ndone!\n");
	return 0;
 
}
