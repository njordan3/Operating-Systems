/* CMPS 3600
 * Jordan Nicholas
 * Lab07: The Producers-Consumers Problem
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>  /*for the intptr_t   */
#include <unistd.h>  /*for the sleep      */
#include <semaphore.h>

#define BUFF_SIZE   5		/* total number of slots */
#define NPROD       3		/* total number of producers */
#define NCONSUM     3		/* total number of consumers */
#define ITEMSPROD   4		/* number of items produced/consumed */

typedef struct {
    int buf[BUFF_SIZE];   /* shared var */
    int in;         	  /* buf[in%BUFF_SIZE] is the first empty slot */
    int out;        	  /* buf[out%BUFF_SIZE] is the first full slot */
    sem_t full;     	  /* keep track of the number of full spots */
    sem_t empty;    	  /* keep track of the number of empty spots */
    sem_t mutex;    	  /* enforce mutual exclusion to shared data */
} sbuf_t;

sbuf_t shared;

void *Producer(void *arg)
{
    int i, item, index;

    index = (intptr_t)arg;

    pthread_detach(pthread_self()); 

    for (i=0; i < ITEMSPROD; i++) {

        /* Produce item */
        item = i;	

        /* Prepare to write item to buf */

        /* If there are no empty slots, wait */
        sem_wait(&shared.empty);
        /* If another thread uses the buffer, wait */
        sem_wait(&shared.mutex);
        shared.buf[shared.in] = item;
        shared.in = (shared.in+1)%BUFF_SIZE;
        printf("[P%d] Producing %d ...\n", index, item); fflush(stdout);
        /* Release the buffer */
        sem_post(&shared.mutex);
        /* Increment the number of full slots */
        sem_post(&shared.full);

        /* Interleave  producer and consumer execution */
        if (i % 2 == 1) sleep(1);
    }
    return NULL;
}

void *Consumer(void *arg)
{
    /* Fill in the code here */
    int i, item, index;

    index = (intptr_t)arg;

    pthread_detach(pthread_self()); 

    for (i=0; i < ITEMSPROD; i++) {
        /* Consume item */
        item = i;
        /* If there are no full slots, wait */
        sem_wait(&shared.full);
        /* If another thread uses the buffer, wait */
        sem_wait(&shared.mutex);
        shared.buf[shared.out] = item;
        shared.out = (shared.out+1)%BUFF_SIZE;
        printf("------> [C%d] Consumed %d\n", index, item); fflush(stdout);
        /* Release the buffer */
        sem_post(&shared.mutex);
        /* Increment the number of empty slots */
        sem_post(&shared.empty);

        /* Interleave  producer and consumer execution */
        if (i % 2 == 1) sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t idP, idC;
    int index;

    sem_init(&shared.full, 0, 0);
    sem_init(&shared.empty, 0, BUFF_SIZE);

    /* Insert code here to initialize mutex*/
    sem_init(&shared.mutex, 0, 1);   

    for (index = 0; index < NPROD; index++)
    {  
       /* Create a new producer */
       pthread_create(&idP, NULL, Producer, (void*)(intptr_t)index);
    }

    /* Insert code here to create NCONSUM consumers */
    for (index = 0; index < NCONSUM; index++)
    {  
       /* Create a new consumer */
       pthread_create(&idC, NULL, Consumer, (void*)(intptr_t)index);
    }
    sem_destroy(&shared.full);
    sem_destroy(&shared.empty);
    sem_destroy(&shared.mutex);
    pthread_exit(NULL);
}
