all: libuthread.so 

libuthread.so: uthread.o ctxswitch.o
	gcc -o libuthread.so -shared uthread.o ctxswitch.o


uthread.o : uthread.c
	gcc -c -g -fPIC -Wall uthread.c
	
	
ctxswitch.o: ctxswitch.s
	as -o ctxswitch.o -c ctxswitch.s

		
clean:
	rm -rf *.o *.so *.a

install:
	cp libuthread.so /usr/local/lib
