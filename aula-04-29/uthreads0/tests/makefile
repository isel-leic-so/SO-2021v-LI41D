
CFLAGS=-Wall -g

all: simpletest singlestep


simpletest: simpletest.c 
	gcc -o simpletest $(CFLAGS)  simpletest.c -luthread

singlestep : singlestep.c
	gcc -o singlestep $(CFLAGS)  singlestep.c -luthread
	
clean:
	rm -rf simpletest singlestep

	
