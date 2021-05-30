all: libuthread.so 

libuthread.so: uthread.o  ctxswitch.o event.o 
	gcc -o libuthread.so -shared uthread.o  event.o ctxswitch.o

 
	
uthread.o : uthread.c
	gcc -c -g -fPIC -Wall uthread.c


semaphore.o : semaphore.c
	gcc -c -g -fPIC -Wall semaphore.c

event.o : event.c
	gcc -c -g -fPIC -Wall event.c
	
ctxswitch.o: ctxswitch.s
	as -o ctxswitch.o -c ctxswitch.s


		
clean:
	rm -rf *.o *.so *.a ctxswitch_test a.out

install:
	sudo cp libuthread.so /usr/local/lib

