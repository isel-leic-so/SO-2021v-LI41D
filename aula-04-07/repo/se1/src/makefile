OBJ=../obj
BIN=../bin

$(BIN)/prog1:	$(OBJ)/src1.o	$(OBJ)/src2.o
	gcc -o $(BIN)/prog1 -Wall $(OBJ)/src1.o	$(OBJ)/src2.o


$(OBJ)/src1.o: src1.c 
	gcc -o $(OBJ)/src1.o -c src1.c


$(OBJ)/src2.o: src2.c 
	gcc -o $(OBJ)/src2.o -c src2.c
	
clean:
	rm -rf $(BIN)/* $(OBJ)/*
