SOLIB = ../lib/bin/solib.so
INCLUDE = ../lib/include/
CC = gcc

CFLAGS = -g -Wall -I$(INCLUDE)
OBJS = $(SRCS:.c=.o)

all: libmath.so client clientdyn smem_child smem_writer smem_reader

libmath.so: math.o
	gcc -o libmath.so -shared math.o

math.o: math.c
	gcc  -c $(CFLAGS) -fpic -Wall math.c
	

client:	client.o  ./libmath.so
	gcc -o client client.o libmath.so 
	
client.o: client.c
	gcc  -c $(CFLAGS) -Wall -g client.c 

clientdyn: clientdyn.o
	gcc -o clientdyn clientdyn.o   $(SOLIB)   -ldl -lrt
	
clientdyn.o: clientdyn.c  
	gcc -c $(CFLAGS) -Wall  clientdyn.c 
	
smem_child: smem_child.c
	gcc -o smem_child $(CFLAGS) -Wall smem_child.c  $(SOLIB)   -lrt

smem_reader: smem_reader.c
	gcc -o smem_reader $(CFLAGS) -Wall smem_reader.c  $(SOLIB) -lrt

smem_writer: smem_writer.c
	gcc -o smem_writer $(CFLAGS) -Wall smem_writer.c  $(SOLIB) -lrt
	
clean:
	rm -f *.so *.o client clientdyn smem_child smem_writer smem_reader
