BIN = bin

 
INCLUDES = -I ~/so2021v/src/SO-2021v-LI41D/lib/include/
CC = gcc
SOLIB = /usr/local/lib/solib.so

CFLAGS = -g -Wall

ECHO_SRV_SRCS = echo_srv.c  
ECHO_SRV_OBJS = $(ECHO_SRV_SRCS:.c=.o)

ECHO_CLI_SRCS = echo_cli.c  
ECHO_CLI_OBJS = $(ECHO_CLI_SRCS:.c=.o)


all: echo_srv echo_cli  

echo_srv:	$(ECHO_SRV_OBJS)
	$(CC) -o echo_srv  $(ECHO_SRV_OBJS) 
	
echo_cli:	$(ECHO_CLI_OBJS)
	$(CC) -o echo_cli  $(ECHO_CLI_OBJS) $(SOLIB) -lrt
	
 

# Compile rule	
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	

clean:
	rm -rf *.o echo_cli echo_srv
	
