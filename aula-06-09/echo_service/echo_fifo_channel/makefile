
INCLUDES = -I ~/so2021v/src/SO-2021v-LI41D/include/ 

CC = gcc
 

CFLAGS = -g -Wall



all: echo_srv echo_cli  

echo_srv:	echo_srv.o
	$(CC) -o echo_srv  echo_srv.o
	
echo_cli:	echo_cli.o
	$(CC) -o echo_cli  echo_cli.o
	
 

# Compile rule	
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< 
	

clean:
	rm -rf *.o echo_cli echo_srv
	
