#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>


int main() {
	int p[2];
	int pids[2];
	
	pipe(p);
	
	// inc 5 | inc
	
	// inc 5
	if ((pids[0] = fork()) == 0) {
		close(p[0]); // não é necessário
		dup2(p[1], 1);
		close(p[1]);
		execlp("inc", "inc", "5", NULL);
		perror("error loading first inc");
		exit(1);
	}
	
	// inc
	if ((pids[1] = fork()) == 0) {
		close(p[1]);
		dup2(p[0], 0);
		close(p[0]);
		execlp("inc", "inc", NULL);
		perror("error loading second inc");
		exit(1);
	}
	
	close(p[0]);
	close(p[1]);
	printf("wait for child termination!\n");
	// wait sobre todos os filhos criados
	for (int i=0; i < 2; ++i) {
		waitpid(pids[i], NULL, 0);
	}
	
	printf("done!\n");
	return 0;
	
}
