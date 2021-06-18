/*
 * implements IP stream socket based echo server using multiplexed I/O with pool
 */


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <limits.h>


#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include <poll.h>

#include "echo_service.h"


// NO TIMEOUT
#define	 INFINITE -1


// size of pending connections queue
#define BACKLOG 5


// globals

static struct pollfd clients[FOPEN_MAX]; 	// client descriptors
static int nclients;						// total current clients
static int listenfd; 						// listen socket



int create_bind_server_socket(const char* ip_addr, int port) {
	int sfd;
	struct sockaddr_in srv_addr;
	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sfd == -1) return -1;
	
 
	/*  bind socket */
	bzero(&srv_addr, sizeof(struct sockaddr_in));
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // inet_addr(ip_addr);
	srv_addr.sin_port = htons(port);
	
	if (bind(sfd, (struct sockaddr *) &srv_addr, sizeof(struct sockaddr_in)) == -1) {
		close(sfd);
		return -3;
	}
	
	return sfd;
}


int add_client(int cfd) {
	
	if (nclients == FOPEN_MAX) return -1;
	clients[nclients].fd = cfd;
	clients[nclients].events = POLLIN | POLLERR;
	nclients++;
	return 0;
}


void rem_client(int cfd, int i) {
	close(cfd);
	clients[i] = clients[--nclients];
}


void process_request(int cfd, echo_msg_t *request) {
	// just echo
	write(cfd, request, sizeof(echo_msg_t));
}

void process(int nready) {
	int cfd; // connection file descriptor
	 
	if (clients[0].revents & POLLIN) { // new connection
		socklen_t clilen = sizeof(struct sockaddr_in);	// client socket addr size
		struct sockaddr_in cliaddr;						// client socket addr
		cfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
		if (cfd == -1) {
			perror("error accepting connection!");
			return;
		}
		printf("connected with %x, port %d...\n", cliaddr.sin_addr.s_addr, cliaddr.sin_port);
	
		if (add_client(cfd) == -1) {
			close(cfd);
			printf("max clients achieved!\n");
			return;
		}
		 
		if (--nready == 0) return;
	}
	for(int i= 1; nready > 0 && i < nclients ; ++i) {
		if (clients[i].revents & (POLLIN | POLLERR)) { 
			cfd = clients[i].fd;
			//printf("data avaiable on socket %d!\n", cfd);
			echo_msg_t request;	// request msg 
			int nr = read(cfd, &request, sizeof(request));
			if (nr <= 0) {
				printf("end of connection!\n");
				rem_client(cfd, i);
				--nready;
			}
			else {	
				process_request(cfd, &request);
			}		
		}
			
	}
			
}


void loop() {
	int nready; 
	
	while(nclients > 0)  {
		nready = poll(clients, nclients, INFINITE);
		printf("there are %d ready descriptors!\n", nready);
		process(nready);	
	}
	
}



int main(int argc, char *argv[]) {
 
    listenfd = create_bind_server_socket(ECHO_SERVER_ADDR, ECHO_SERVER_PORT);
	if (listenfd == -1) {
		printf("socket creation error!\n");
		return 1;
	}
	
	// set listen queue size
	if (listen(listenfd, BACKLOG) == -1) {
		fprintf(stderr, "error setting  listen queue size\n");
		close(listenfd);
		return 1;
	}
	
	add_client(listenfd);
	 
	
	// run the event loop
	loop();
	
	return 0;
 
}


 
