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

 


#include "meminfo.h"

 
 

int main(int argc, char *argv[])
{
	 
	show_avail_mem("Mem info");
	 
	 
	return 0;
}
