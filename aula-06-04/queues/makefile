CFLAGS= -Wall -I../include/

queue_test: queue_test.c queue.c
	gcc -o queue_test $(CFLAGS) queue_test.c queue.c -pthread

clean:
	rm -f queue_test
	
	
