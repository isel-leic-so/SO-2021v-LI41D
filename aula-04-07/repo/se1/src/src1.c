#include <stdio.h>

#include "src2.h"


/**------------------------------
 * To exec prog1 from src you can:
 * use relative path to bin: 
 * 
 * ../bin/prog1
 * 
 * or add ../bin to PATH doing this on bash:
 * 
 * PATH=$PATH:../bin
 * 
 * after this, on that shell session you can simply call:
 * 
 * prog1
 *
 *------------------------------------*/
 
 
int main() {
	printf("hello from main\n");
	f1();
}
