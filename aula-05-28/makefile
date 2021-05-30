all: tp_adder

CFLAGS= -I ../uthreads/include -Wall
	
tp_adder: tp_adder.c queue.c cdl.c tpool.c chrono.c
	gcc -o tp_adder $(CFLAGS)  tp_adder.c queue.c cdl.c chrono.c tpool.c -pthread

clean:
	rm -f tp_adder 
	
