
#include <sys/epoll.h>


// NO TIMEOUT
#define	 INFINITE -1

// MAXIMUM READY HANDLES
#define EPOOL_MAX_FDS 1024


// async handles

struct async_handle_impl;

typedef struct async_handle_impl *async_handle_t;

typedef void (*async_cb)(async_handle_t ash,  void *ctx);


struct  async_handle_impl {
	int fd; // associated file descriptor
	async_cb cb;
	void *ctx;
};


// async operations


int ah_init();
	 
async_handle_t ah_regist_fd(int fd);

int ah_getfd(async_handle_t ah); 

void ah_accept_async(async_handle_t ah, async_cb accept_cb, void *ctx);

void ah_read_async(async_handle_t ah, async_cb read_cb, void *ctx);
 
void ah_close(async_handle_t ah);
	 
void ah_loop();

