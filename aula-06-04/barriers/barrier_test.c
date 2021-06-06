
/*
 *  barrier1.c
*/

#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include "barrier.h"

#define PARTIES 3

barrier_t   barrier; // the barrier synchronization object
pthread_t t1, t2;


static void check_awaker(char *thread_name, int index) {
	if (index == PTHREAD_BARRIER_SERIAL_THREAD) {
		printf("\nthe awaker thread is  %s\n", thread_name);
	}
}


static void start_phase(char *phase_name, char *thread_name) {
	time_t  now;
    char    buf [27];
	
    time (&now);
    printf ("phase %s on %s starting at %s", phase_name, thread_name, ctime_r (&now, buf));
}

static void end_phase(char *phase_name, char *thread_name) {
	time_t  now;
    char    buf [27];
    
    check_awaker(thread_name,  barrier_await(&barrier));
    
    // after this point, all three threads have completed.
    time (&now);
    printf ("barrier for phase %s in %s done at %s", phase_name, thread_name, ctime_r (&now, buf));
}

void * thread1 (void *arg)
{
    start_phase("phase 1", "thread 1");

    // do the computation
    // let's just do a sleep here...
    sleep (rand() % 5);
   
	end_phase("phase 1", "thread 1");
	
	start_phase("phase 2", "thread 1");
	  // do the computation
    // let's just do a sleep here...
    sleep (rand() % 10);
    
    end_phase("phase 2", "thread 1");
    return NULL;
}

void *thread2 (void *arg)
{
	start_phase("phase 1", "thread 2");

    // do the computation
    // let's just do a sleep here...
    sleep (rand() % 10);
   
	end_phase("phase 1", "thread 2");
	
	start_phase("phase 2", "thread 2");
	  // do the computation
    // let's just do a sleep here...
    sleep (rand() % 5);
    
    end_phase("phase 2", "thread 2");
    return NULL;
}



int main () 
{
    
    // create a barrier object with a count of PARTIES
    barrier_init (&barrier, PARTIES);

    // start up two threads, thread1 and thread2
    pthread_create (&t1, NULL, thread1, NULL);
    pthread_create (&t2, NULL, thread2, NULL);

   
    start_phase("phase 1", "thread _main");
    // do the computation
    // let's just do a sleep here...
    sleep (rand() % 10);
	end_phase("phase 1", "thread _main");
	
	
	
	start_phase("phase 2", "thread _main");
	// do the computation
    // let's just do a sleep here...
    sleep (rand() % 5);
    
    end_phase("phase 2", "thread _main");
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
