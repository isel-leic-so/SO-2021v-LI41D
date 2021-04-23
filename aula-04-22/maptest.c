
/*-----------------------------------------------------------------
 * This program illustrates the behaviour of a file map operation
 * by showing several virtual memory stats at selected phases in
 * program execution
 * 
 * Build:
 * 		gcc -o maptest -Wall maptest.c ../utils/memutils.c
 * 
 * Isel, 2020
 *----------------------------------------------------------------*/
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#define MB (1024 *1024)

#include "meminfo.h"
#include "memutils.h"


long sum_ints(int *ints, int len) {
	long sum =0;
	 
	for(int i=len/2, j=len/2-1; i < len;i++, j--) {
		sum += ints[i];
		sum += ints[j];
		//show_avail_mem("one more page");
		//phase_start("next");
	
	}
	
	/*
	for(int i=0; i < len;i++) {
		sum += ints[i];
		 
		//show_avail_mem("one more page");
		//phase_start("next");
	
	}
	*/
	return sum;
}

long inc_ints(int *ints, int len) {
	long sum =0;
	for(int i=0; i < len;i++) {
		ints[i]++;
		
		//show_avail_mem("one more page");
		//phase_start("next");
	
	}
	return sum;
}

int main(int argc, char *argv[]) {
	if (argc <2 || argc > 3) {
		printf("usage: maptest <file>  [<size>]\n");
		return 1;
	}
	
	void  *fmap = NULL;
	long size = 0;
	
	if (argc == 3)  
		size = atol(argv[2]);
	printf("size=%ld MBytes\n", size);
	size *= MB;
	
	
	show_avail_mem("Inicio");
	phase_start("file map");
	
	fmap = map_file(argv[1],  size);
	if (fmap == NULL) {
		perror("error %d mapping the file");
		return 2;
	}
	
	printf("mapped at %p\n", fmap);
	show_avail_mem("depois do map");

	phase_start("read");
	
	long sum = sum_ints((int *) fmap, size/sizeof(int));
	printf("sum=%ld\n", sum);
	
	show_avail_mem("depois do read");
	phase_start("incrementar os elementos");
	
	// decomment the next line to change the mapped file
	
	inc_ints((int*) fmap, size/sizeof(int));
	show_avail_mem("depois do write");
	phase_start("unmap");
	
	unmap_file(fmap, size);
	show_avail_mem("depois do unmap");
	phase_start("terminar");
	return 0;
}
