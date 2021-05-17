
CFLAGS=-Wall -g

all: simpletest singlestep join_test


simpletest: simpletest.c 
	gcc -o simpletest $(CFLAGS)  simpletest.c -luthread

singlestep : singlestep.c
	gcc -o singlestep $(CFLAGS)  singlestep.c -luthread

join_test : join_test.c
	gcc -o join_test $(CFLAGS)  join_test.c -luthread
	
	
clean:
	rm -rf simpletest singlestep

	
