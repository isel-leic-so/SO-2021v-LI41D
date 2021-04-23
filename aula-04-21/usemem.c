/*----------------------------------------------------------------
 *  This program dynamically allocs a big buffer
 *  using it for read and write before 
 *  create a child that uses the inherited buffer for read an write.
 * 
 *  For each step it show mem info stats
 * 
 * The program ilustrates the Copy On Write (COW) 
 * that occurrs on child creation
 *
 * Isel, 2020
 * 
 * Build:
 * 		gcc -o mem2 -Wall mem2.c ../utils/memutils.c
 * 
 *---------------------------------------------------------------*/

 
#include <stdio.h>
#include <stdlib.h>
#include "meminfo.h"


#define MB (1024*1024)
#define CHUNK_MB 300
#define CHUNK_SIZE (MB*CHUNK_MB)


void allocate_chunk() {
	char *ptr = malloc(CHUNK_SIZE);
	if (ptr == NULL) {
		perror("memory error");
		exit(1);
	}
	for(int i=0; i < CHUNK_SIZE; ++i) 
		ptr[i] = i % 256;
	
}
 

int main(int argc, char *argv[])
{
	show_avail_mem("Mem info");
	while(1) {
		printf("Press enter to allocate one more %d MBytes chunk..", CHUNK_MB);
		getchar();
		allocate_chunk();
		show_avail_mem("Mem info");
	
	}
	
	 
	 
	return 0;
}
