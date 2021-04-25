SOLIB = ../lib/bin/solib.so
INCLUDE = ../lib/include/
CC = gcc

CFLAGS = -g -Wall -I$(INCLUDE)
OBJS = $(SRCS:.c=.o)
all:	mem2 showmem usemem 

mem2: mem2.o
	gcc -o mem2  mem2.o $(SOLIB) -lrt


	
showmem: showmem.o
	gcc -o showmem showmem.o $(SOLIB) -lrt
	
usemem: usemem.o
	gcc -o usemem usemem.o $(SOLIB) -lrt 

# Compile rule	
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	

clean:
	rm -rf *.o mem2 showmem usemem
	
