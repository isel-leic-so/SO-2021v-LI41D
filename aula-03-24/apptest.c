
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[], char *env[]) {
	// show passed arguments
	
	sleep(5);
	
	printf("args:\n");
	for(int i=0; i < argc; i++) {
		printf("argc[%d]=%s\n", i, argv[i]);
		
	}
	
	// show process environment variables
	
	printf("\nenvironment variables\n");
	
	while(*env != NULL) {
		printf("%s\n", *env);
		env++;
	}
	
	return 0;
}
