#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>


int main() {
	int p[2];
	int pid_child;
	
	pipe(p);
	
	if ((pid_child = fork())==0) {
		close(p[0]);
		// child process
		char msg[] = "hello from child!\n";
		
		write(p[1], msg, strlen(msg)+1);
		exit(0);	
	}
	
	char recvd_msg[256];
	char *pmsg = recvd_msg;
	
	close(p[1]); // necessário para rarantir que não mais escritores no pipe de modo a que o read termine

	while (read(p[0], pmsg, 1) != 0) {
		putchar(*pmsg);
		fflush(stdout);
		pmsg++;
		
	}
	close(p[0]);
	
	printf("%d bytes read from pipe\n", (int) (pmsg - recvd_msg));
	printf("msg: %s\n", recvd_msg);
	
	waitpid(pid_child, NULL, 0);
	
	return 0;
}
