
#include <unistd.h>

int my_write(int fd, const void *buf, int size);

int main() {
	my_write(1, "hello again!", 12);
	return 0;
}
