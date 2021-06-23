/**
 * this is a version of the worker server that illustrate
 * the use of the thread pool for leaving the I/O pool time 
 * to maximize the I/O processing
 * where the request processing consumes CPU time (wich is really not the case
 * of the echo server, of course :) )
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>
#include <unistd.h>

#include "echo_service.h"

 
#define DEFAULT_BACKLOG 128


// globals
static uv_loop_t loop;
static uv_tcp_t server;	

// just for stat purposes
static int nreads =0;



/**
  A wrapper that allow the write completed callback
  to free the associated buffer
  In this version is not used, since the buffer is 
  associated to uv_write_t via is "data" field 
*/
typedef struct {
    uv_write_t req;
    uv_buf_t buf;
} write_req_t;


void free_write_req(uv_write_t *req) {
	// the old way
    //write_req_t *wr = (write_req_t*) req;
    //free(wr->buf.base);
    
    // the new version that use the "data field" of uv_write_t request
    // the allow the free of the associated buffer
    free(req->data);
    free(req);
}


void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
	printf("alloc buf called!\n");
    buf->base = (char*) malloc(suggested_size);
    buf->len = suggested_size;
}

void on_close(uv_handle_t* handle) {
	// here the loop associated handle is freed
    free(handle);
}

// the write completion callback
//
void echo_write_completed(uv_write_t *req, int status) {
    if (status) {
        fprintf(stderr, "Write error %s\n", uv_strerror(status));
    }
    free_write_req(req);
}


// the wrapper to mantain the state
// associated to the request being processed
// on libuv thread pool
typedef struct uv_echo_work {
	uv_work_t req;
	uv_stream_t *client;
	uv_buf_t buf;
} uv_echo_work_t;


/**
 *  the actual worker
 *  Here, since we have a simple echo server
 *  the "work" is simulated by a sleep
*/
void do_work(uv_work_t *w) {
	sleep(1);
	printf("do work in thread %ld\n", uv_thread_self());
}


/**
 * The after callback that executes in the I/O loop thread
 * Has is required for use of the associated handles
 * Here we send the response to our client
 */
void send_resp(uv_work_t *w, int status) {
	uv_echo_work_t *wreq = (uv_echo_work_t *) w;
	
	printf("send_resp in thread %ld\n", uv_thread_self());
	
	uv_write_t *req = malloc(sizeof(uv_write_t));    
	req->data = wreq->buf.base; 
	uv_write((uv_write_t*) req, wreq->client, &wreq->buf, 1, echo_write_completed);
}


/**
 * Prepare and submit the work to the libuv thread pool
 */
static void dispatch_work(uv_stream_t *client, ssize_t nread, void *data) {
	uv_echo_work_t *req = malloc(sizeof(uv_echo_work_t));
	req->client = client;
	req->buf = uv_buf_init(data, nread);
	
	uv_queue_work(&loop, (uv_work_t *) req, do_work, send_resp);
}


/**
 * the callback for processed of each buffer with data received from client
 */
void echo_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf) {
	//printf("echo_read %d\n", nreads);

    if (nread > 0) {
		++nreads;
		/*
        write_req_t *req = (write_req_t*) malloc(sizeof(write_req_t));
        req->buf = uv_buf_init(buf->base, nread);
        */
        
        dispatch_work(client, nread, buf->base);
        
        return;
    }
    if (nread < 0) {
        if (nread != UV_EOF)
            fprintf(stderr, "Read error %s\n", uv_err_name(nread));
		printf("%d total reads in connection %p\n", nreads, client);
        uv_close((uv_handle_t*) client, on_close);
    }

    free(buf->base);
}


/**
 * The caclback for resolve a new client connection
 */
void on_new_connection(uv_stream_t *server, int status) {
    if (status < 0) {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        return;
    }

	
    uv_tcp_t *client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
    uv_tcp_init(&loop, client);
    printf("new connection for client %p\n", client);
    if (uv_accept(server, (uv_stream_t*) client) == 0) {
        uv_read_start((uv_stream_t*) client, alloc_buffer, echo_read);
    }
    else {
        uv_close((uv_handle_t*) client, on_close);
    }

}


int main() {
	struct sockaddr_in addr;
    uv_loop_init(& loop);

    uv_tcp_init(&loop, &server);
    
    uv_ip4_addr(ECHO_SERVER_ADDR, ECHO_SERVER_PORT, &addr);

    uv_tcp_bind(&server, (const struct sockaddr*)&addr, 0);
    
    int r = uv_listen((uv_stream_t*) &server, DEFAULT_BACKLOG, on_new_connection);
    
    if (r) {
        fprintf(stderr, "Listen error %s\n", uv_strerror(r));
        return 1;
    }
    uv_run(&loop, UV_RUN_DEFAULT);
    
    uv_loop_close(&loop);
    return 0;
}
