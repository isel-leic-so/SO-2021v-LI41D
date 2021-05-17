all: libuthread.so ctxswitch_test libuthread0.so

libuthread.so: uthread.o ctxswitch.o
	gcc -o libuthread.so -shared uthread.o ctxswitch.o

libuthread0.so: uthread0.o ctxswitch0.o
	gcc -o libuthread0.so -shared uthread0.o ctxswitch0.o
	
	
uthread.o : uthread.c
	gcc -c -g -fPIC -Wall uthread.c

uthread0.o : uthread0.c
	gcc -c -g -fPIC -Wall uthread0.c
	
	
ctxswitch.o: ctxswitch.s
	as -o ctxswitch.o -c ctxswitch.s


	
ctxswitch_test: 	ctxswitch_test.c 
	gcc -o ctxswitch_test -Wall -g ctxswitch_test.c ctxswitch0.s
		
clean:
	rm -rf *.o *.so *.a ctxswitch_test

install:
	cp libuthread.so /usr/local/lib
	cp libuthread0.so /usr/local/lib
