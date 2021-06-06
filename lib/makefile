BIN = bin
INCLUDES = -Iinclude
CC = gcc

CFLAGS = -fPIC -g -Wall

SRCS = meminfo.c sysutils.c memutils.c chrono.c

OBJS = $(SRCS:.c=.o)

$(BIN)/solib.so:	$(OBJS)
	$(CC) -o $(BIN)/solib.so -shared $(OBJS)

# Compile rule	
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	

install:
	sudo cp bin/solib.so /usr/local/lib
clean:
	rm -rf *.o $(BIN)/*
	
