/* CMPS 3600
 * Jordan Nicholas
 * Lab09: The Dining Philosphers Problem
 */

#include <stdio.h>  
#include <pthread.h> 
#include <stdlib.h> 
#include <stdint.h>
#include <unistd.h>
#include <time.h>

#define THREAD_NUM 5
#define MAX_MEALS 2
#define TRUE  1 
#define FALSE 0

/* time tools */
time_t rawtime;
struct tm* timeInfo;
char buffer[80];

/* mutex locks for each chopstick */  
pthread_mutex_t C0, C1, C2, C3, C4;

/* number of meals completed by each philospher */  
int numMeals[THREAD_NUM]={0,0,0,0,0};  

void *eat(void *); /* prototype of eat routine */  


int main()  
{  
    pthread_t tid[THREAD_NUM]; 
    void *status; 
    
    if (pthread_mutex_init(&C0, NULL)) {
        printf("Mutex C0 was not initialized correctly..\n");
        exit(0);
    }
    if (pthread_mutex_init(&C1, NULL)) {
        printf("Mutex C1 was not initialized correctly..\n");
        exit(0);
    }
    if (pthread_mutex_init(&C2, NULL)) {
        printf("Mutex C2 was not initialized correctly..\n");
        exit(0);
    }
    if (pthread_mutex_init(&C3, NULL)) {
        printf("Mutex C3 was not initialized correctly..\n");
        exit(0);
    }
    if (pthread_mutex_init(&C4, NULL)) {
        printf("Mutex C4 was not initialized correctly..\n");
        exit(0);
    }

    /* create 5 threads representing 5 philosphers */  
    for (int i = 0; i < THREAD_NUM; i++)  
    {
        /*Your code here */
        pthread_create(&tid[i], NULL, eat, (void*)(intptr_t)i);
    }  

    /* wait for the join of 5 threads */  
    for (int i = 0; i < THREAD_NUM; i++)
    {  
        /*Your code here */
        if (pthread_join(tid[i], NULL)) {
            printf("Error joining thread\n");
            exit(1);
        }
    }   

    printf("\nThe philophers have all finished their meals!\n");  

    pthread_mutex_destroy(&C0);
    pthread_mutex_destroy(&C1);
    pthread_mutex_destroy(&C2);
    pthread_mutex_destroy(&C3);
    pthread_mutex_destroy(&C4);
    return (0);  
}

void *eat(void  *arg)  
{
    int index = (intptr_t)arg; 
    while((numMeals[0] < MAX_MEALS) ||
          (numMeals[1] < MAX_MEALS) ||
          (numMeals[2] < MAX_MEALS) ||
          (numMeals[3] < MAX_MEALS) ||
          (numMeals[4] < MAX_MEALS)) {
        if(index==0 && numMeals[0] < MAX_MEALS) {
            if (pthread_mutex_trylock(&C0) == 0) {
                if (pthread_mutex_trylock(&C1) == 0) {
                    time(&rawtime);
                    timeInfo = localtime(&rawtime);
                    strftime(buffer,80,"Philosopher 1 has started eating at %T",timeInfo);
                    puts(buffer);
                    numMeals[index]++;
                    sleep(2);
                    time(&rawtime);
                    timeInfo = localtime(&rawtime);
                    strftime(buffer,80,"Philosopher 1 has finished eating at %T",timeInfo);
                    puts(buffer);
                    // unlock both chopsticks
                    pthread_mutex_unlock(&C0);  
                    pthread_mutex_unlock(&C1);  
                } else 
                    // release this chopstick if the other isn't available
                    pthread_mutex_unlock(&C0);  
            }
        }
        if(index==1 && numMeals[1] < MAX_MEALS) {
            if (pthread_mutex_trylock(&C1) == 0) {
                if (pthread_mutex_trylock(&C2) == 0) {
                    time(&rawtime);
                    timeInfo = localtime(&rawtime);
                    strftime(buffer,80,"Philosopher 2 has started eating at %T",timeInfo);
                    puts(buffer);
                    numMeals[index]++;
                    sleep(2);
                    time(&rawtime);
                    timeInfo = localtime(&rawtime);
                    strftime(buffer,80,"Philosopher 2 has finished eating at %T",timeInfo);
                    puts(buffer);
                    // unlock both chopsticks
                    pthread_mutex_unlock(&C1);  
                    pthread_mutex_unlock(&C2);  
                } else
                    // release this chopstick if the other isn't available
                    pthread_mutex_unlock(&C1);  
            }
        } 
        if(index==2 && numMeals[2] < MAX_MEALS) {
            if (pthread_mutex_trylock(&C2) == 0) {
                if (pthread_mutex_trylock(&C3) == 0) {
                    time(&rawtime);
                    timeInfo = localtime(&rawtime);
                    strftime(buffer,80,"Philosopher 3 has started eating at %T",timeInfo);
                    puts(buffer);
                    numMeals[index]++;
                    sleep(2);
                    time(&rawtime);
                    timeInfo = localtime(&rawtime);
                    strftime(buffer,80,"Philosopher 3 has finished eating at %T",timeInfo);
                    puts(buffer);
                    // unlock both chopsticks
                    pthread_mutex_unlock(&C2);  
                    pthread_mutex_unlock(&C3);  
                } else
                    // release this chopstick if the other isn't available
                    pthread_mutex_unlock(&C2);  
            }
        } 
        if(index==3 && numMeals[3] < MAX_MEALS) {
            if (pthread_mutex_trylock(&C3) == 0) {
                if (pthread_mutex_trylock(&C4) == 0) {
                    time(&rawtime);
                    timeInfo = localtime(&rawtime);
                    strftime(buffer,80,"Philosopher 4 has started eating at %T",timeInfo);
                    puts(buffer);
                    numMeals[index]++;
                    sleep(2);
                    time(&rawtime);
                    timeInfo = localtime(&rawtime);
                    strftime(buffer,80,"Philosopher 4 has finished eating at %T",timeInfo);
                    puts(buffer);
                    // unlock both chopsticks
                    pthread_mutex_unlock(&C3);  
                    pthread_mutex_unlock(&C4);  
                } else
                    // release this chopstick if the other isn't available
                    pthread_mutex_unlock(&C3);  
            }
        } 
        if(index==4 && numMeals[4] < MAX_MEALS) {
            if (pthread_mutex_trylock(&C4) == 0) {
                if (pthread_mutex_trylock(&C0) == 0) {
                    time(&rawtime);
                    timeInfo = localtime(&rawtime);
                    strftime(buffer,80,"Philosopher 5 has started eating at %T",timeInfo);
                    puts(buffer);
                    numMeals[index]++;
                    sleep(2);
                    time(&rawtime);
                    timeInfo = localtime(&rawtime);
                    strftime(buffer,80,"Philosopher 5 has finished eating at %T",timeInfo);
                    puts(buffer);
                    // unlock both chopsticks
                    pthread_mutex_unlock(&C4);  
                    pthread_mutex_unlock(&C0);  
                } else
                    // release this chopstick if the other isn't available
                    pthread_mutex_unlock(&C4);  
            }
        }
    }
    pthread_exit(0);  
} 
