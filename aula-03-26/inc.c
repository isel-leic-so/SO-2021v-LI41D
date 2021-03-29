#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int num;
	
	
	if (argc > 1) {
		num = atoi(argv[1]);
	}
	else {
		scanf("%d", &num);
	}
	 
	printf("%d", num+1);
	
	fprintf(stderr, "pid =%d, parent pid = %d\n", 
					getpid(), getppid());
	return 0;
}
