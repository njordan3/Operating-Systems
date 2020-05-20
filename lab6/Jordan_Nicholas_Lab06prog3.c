/*
 * CMPS 3600
 * Jordan Nicholas
 * Lab06
 */

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define THREAD_COUNT 10 //define thread count

int count = 0;  //global count variable

pthread_mutex_t lock;   //globl mutex

void *Count(void *a)
{
    pthread_mutex_lock(&lock);  //lock mutex while a thread is running in CS
    printf("Count = %d\n", ++count);
    sleep(1);   //delay 1 second between each thread
    pthread_mutex_unlock(&lock);    //unlock mutex
}

int main(int argc, char *argv[])
{
    pthread_t tid[THREAD_COUNT];  //create threads

    if (pthread_mutex_init(&lock, NULL)) { //initialize mutex
        printf("Mutex was not initialized correctly...\n");
        exit(1);
    }
    for (int i = 0; i < THREAD_COUNT; i++) {
        if(pthread_create(&tid[i], NULL, Count, NULL)) {
            printf("ERROR creating thread %d\n", i);
            exit(1);
        }

    }
    for (int i = 0; i < THREAD_COUNT; i++) {
        if(pthread_join(tid[i], NULL)) {    //wait for threads to finish
            printf("ERROR joining thread %d\n", i);
            exit(1);
        }

    } 
    if (count != THREAD_COUNT)
        printf("\n BOOM! count is [%d], should be %d\n\n", count, THREAD_COUNT);
    else
        printf("\n OK! count is [%d]\n\n", count);

    pthread_exit(NULL);
    pthread_mutex_destroy(&lock);
}


