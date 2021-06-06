
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "queue.h"

#define MAX_MSG 128

#define MSG_SIZE(m) (strlen(m)+1)

static queue_t queue;

void* sender(void * arg) {
 	
	printf("sender thread begin\n");
	char msg[MAX_MSG];
	
	strcpy(msg, "hello, ");

	queue_put(&queue, msg, MSG_SIZE(msg));
	 	
	sprintf(msg, "from thread %ld", pthread_self());
	queue_put(&queue, msg, MSG_SIZE(msg));
	queue_put(&queue, "", 1);
	printf("sender thread end\n");
	return NULL;
}


void* receiver(void * arg) {
	 
	char msg[MAX_MSG];
	
	printf("receiver thread  begin\n");
	
	while(true) {
		printf("receiver: ask for more...\n");
		queue_get(&queue, msg, MAX_MSG);
		if (msg[0] == 0) break; // empty msg
		printf("received: '%s'\n", msg);
		
	}
	
	printf("receiver thread  end\n");
	return NULL;
}

 

int main() {
	pthread_t tsender;
	pthread_t treceiver;
	
	queue_init(&queue, 1);
	
	printf("queue test  begin\n");
	
	 
	pthread_create(&tsender, NULL, sender, NULL);
	pthread_create(&treceiver, NULL, receiver, NULL);
	
	
	pthread_join(tsender, NULL);
	pthread_join(treceiver, NULL);
	
	printf("queue test  end\n");
    return 0;
}
