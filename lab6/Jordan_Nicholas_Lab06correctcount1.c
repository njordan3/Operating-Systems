/*
 * CMPS 3600
 * Jordan Nicholas
 * Lab06
 */

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define ITERAT 1000000

int TOTAL = 0;

sem_t sem;  //global semaphore

void *Count(void *a)
{
    sem_wait(&sem); //lock the semaphore so the second thread can't continue
    int i, tmp;
    for(i = 0; i < ITERAT; i++)
    {
        tmp = TOTAL;      /* copy the global TOTAL locally */
        tmp = tmp+1;    /* increment the local copy */
        TOTAL = tmp;      /* store the local value into the global TOTAL */ 
    }
    sem_post(&sem);     //unlock the semaphore so the second thread can run
}

int main(int argc, char *argv[])
{
    pthread_t tid1, tid2;

    if (sem_init(&sem, 0, 1)) { //initialize semaphore as unlocked
        printf("Semaphore was not initialized correctly...\n");
        exit(1);
    }

    if(pthread_create(&tid1, NULL, Count, NULL))
    {
      printf("\n ERROR creating thread 1");
      exit(1);
    }
    if(pthread_create(&tid2, NULL, Count, NULL))
    {
      printf("\n ERROR creating thread 2");
      exit(1);
    }

    if(pthread_join(tid1, NULL))	/* wait for the thread 1 to finish */
    {
      printf("\n ERROR joining thread");
      exit(1);
    }

    if(pthread_join(tid2, NULL))        /* wait for the thread 2 to finish */
    {
      printf("\n ERROR joining thread");
      exit(1);
    }

    if (TOTAL != 2 * ITERAT) 
        printf("\n BOOM! TOTAL is [%d], should be %d\n\n", TOTAL, 2*ITERAT);
    else
        printf("\n OK! TOTAL is [%d]\n\n", TOTAL);
  
    pthread_exit(NULL);
    sem_destroy(&sem);
}


