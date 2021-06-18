#include <uv.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static uv_loop_t loop;
static uv_tty_t input;


static void on_closed(uv_handle_t *handle) {
	printf("input closed|\n");
}

static void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
	buf->base = malloc(suggested_size);
	buf->len = suggested_size;
}


static void on_read_completion(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf) {
	buf->base[nread] = 0;
	printf("readed bytes from input: '%s'\n", buf->base);
	if (strcmp(buf->base, "exit\n") == 0) {
		uv_close((uv_handle_t *) stream, on_closed);
		printf("after close!\n");
	}
	free(buf->base);
}

int main() {
	
	
	int res = uv_loop_init(&loop);
	if (res != 0)  {
		printf("error initializing loop!\n");
		return 1;
	}
	
	uv_tty_init(&loop, &input, 0 /* standard input */, 0 /* not used */);
	uv_read_start((uv_stream_t *) &input, alloc_buffer, on_read_completion);
	
	printf("start loop!\n");
	uv_run(&loop, UV_RUN_DEFAULT);
	
	printf("loop terminated!\n");
	
	uv_loop_close(&loop);
	
	return 0;

}
