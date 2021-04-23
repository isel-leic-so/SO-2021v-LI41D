/*---------------------------------------------------------------------
 * This program used mmap mechanism to create 
 * a  large binary file of integers in an efficient way
 * Build:
 * 		gcc -o genints -Wall genints.c ../utils/memutils.c
 * 
 * Isel, 2020
 *-------------------------------------------------------------------*/

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>

#include "meminfo.h"
#include "memutils.h"

#define MB (1024*1024)


int main(int argc, char *argv[]) {
	if (argc < 2 || argc > 3) {
		printf("usage: genints <size_in_megas> [ <file> ] \n");
		return 1;
	}
	
	const char *file = "intfile.dat";
	
	long  size = atol(argv[1]);
	if (size==0) {
		printf("invalid size number!\n");
		return 1;
	}
	
	printf("size =%ld MBytes\n", size);
	
	size *= MB;
	if (argc == 3) {
		file = argv[2];
	}
 
	void *fmap = NULL;
    
	
	if ( (fmap = map_file(file, size )) == NULL) {
		perror("error mapping file");
		return 1;
	}
	int *ints = (int *) fmap;
	
	for(int i=0; i < size/sizeof(int); ++i) {
		ints[i] = 1;
		
		if ( ((i+1) % (100*MB)) == 0 ) {
			show_avail_mem("after another chunk");
			phase_start("more chunks");;
		}
	}
	show_avail_mem("file created");
	phase_start("terminate");
	unmap_file(fmap, size);
	return 0;
}
