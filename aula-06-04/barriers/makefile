CFLAGS= -Wall -I../include/

barrier_test: barrier_test.c barrier.c
	gcc -o barrier_test $(CFLAGS) barrier_test.c barrier.c -pthread
	
clean:
	rm barrier_test
		
	
	
