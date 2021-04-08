OBJ=../obj
BIN=../bin

all:
	prog1
	
	
$(BIN)/prog1:	$(OBJ)/src1.o	$(OBJ)/src2.o
	gcc -o $(BIN)/prog1 -Wall $(OBJ)/src1.o	$(OBJ)/src2.o


$(OBJ)/src1.o: src1.c 
	gcc -o $(OBJ)/src1.o -c src1.c


$(OBJ)/src2.o: src2.c 
	gcc -o $(OBJ)/src2.o -c src2.c


create:
	@if [ ! -d "../bin" ]; then echo "Create bin directory"; mkdir ../bin; fi
	@if [ ! -d "../obj" ]; then echo "Create obj directory"; mkdir ../obj; fi

clean:
	rm -rf $(BIN)/* $(OBJ)/*
