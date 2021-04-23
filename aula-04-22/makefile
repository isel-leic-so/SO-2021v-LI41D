SOLIB = ../lib/bin/solib.so
INCLUDE = ../lib/include/
CC = gcc

CFLAGS = -g -Wall -I$(INCLUDE)
OBJS = $(SRCS:.c=.o)
all:	genints maptest pframes

genints: genints.o
	gcc -o genints  genints.o $(SOLIB) -lrt

maptest: maptest.o
	gcc -o maptest maptest.o $(SOLIB) -lrt
	
pframes: pframes.o
	gcc -o pframes pframes.o $(SOLIB) -lrt 

# Compile rule	
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	

clean:
	rm -rf *.o genints pframes maptest
	
