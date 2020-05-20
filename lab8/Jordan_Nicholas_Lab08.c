/* CMPS 3600
 * Jordan Nicholas
 * Lab08: The Racers Problem
 */

/*****************************************************************************/
/*****************************************************************************/
// 
//Program Description:							
// We assume two racers, at two diagonally opposite corner of a rectangular 
// region. They have to traverse along the roads along the peripheri of the 
// region. There are two bridges on two opposite sides of the rectangle. 
// In order to complete one round of traversal around this, the racers have   
// to get pass for both the bridge at a time. The conditions of the race are 
// 1) Only one racer can get a pass at a time. 
// 2) Before one starts one round, he has to request and get both the passes  
//    and then after finishing that round has to release the passes, and make  
//    new try to get those passes for the next round.			
// 3) Racer1 (R1) will acquire bridge-pass B1 first, then B0. 
//    R0 will acquire B0 and then B1. 
// 4) There is a maximum number of rounds prefixed. Whoever reaches that number
//    first will be the winner and the race will stop. 
// 
// This is how the situation looks before starting. 
//	
// 
//		    	       B0 
//           R0-------- ~  -------------
//		     |	                	    | 
//		     |			                | 
//		     |			                | 
//		     |			                | 
//		     --------- ~  ------------- R1
//			           B1 
// 
// The main function simulates two threads for two racers. 
//
// COMPILATION:  gcc Racers2.c -o Racers2 -lpthread -D_REENTRANT
// COMPILATION:  gcc Racers2.c -o Racers2 -pthread -D_REENTRANT
// 
/*****************************************************************************/
/*****************************************************************************/

#include<stdio.h>  
#include<pthread.h> 
#include<stdlib.h> 
#include<stdint.h>

#define THREAD_NUM 2  
#define MAX_ROUNDS 200000
#define TRUE  1 
#define FALSE 0


/* mutex locks for each bridge */  
pthread_mutex_t B0, B1;

/* racer ID */ 
int r[THREAD_NUM]={0,1};  

/* number of rounds completed by each racer */  
int numRounds[THREAD_NUM]={0,0};  


void *racer(void *); /* prototype of racer routine */  


int main()  
{  
    pthread_t tid[THREAD_NUM]; 
    void *status; 
    int i,j;  
    
    if (pthread_mutex_init(&B0, NULL)) {
        printf("Mutex B0 was not initialized correctly..\n");
        exit(0);
    }
    if (pthread_mutex_init(&B1, NULL)) {
        printf("Mutex B1 was not initialized correctly..\n");
        exit(0);
    }

    /* create 2 threads representing 2 racers */  
    for (i = 0; i < THREAD_NUM; i++)  
    {
        /*Your code here */
        pthread_create(&tid[i], NULL, racer, (void*)(intptr_t)i);
    }  

    /* wait for the join of 2 threads */  
    for (i = 0; i < THREAD_NUM; i++)
    {  
        /*Your code here */
        if (pthread_join(tid[i], NULL)) {
            printf("Error joining thread\n");
            exit(1);
        }
    }   

    printf("\n");  
    for(i=0; i<THREAD_NUM; i++)  
        printf("Racer %d finished %d rounds!!\n", i, numRounds[i]);  

    if(numRounds[0]>=numRounds[1]) printf("\n RACER-0 WINS.\n\n");  
    else  printf("\n RACER-1 WINS..\n\n");  

    pthread_mutex_destroy(&B0);
    pthread_mutex_destroy(&B1);
    return (0);  
}  

void *racer(void  *arg)  
{   
    int index = (intptr_t)arg; 
    while( (numRounds[0] < MAX_ROUNDS) && (numRounds[1] < MAX_ROUNDS) )  
    {  
        /* RACER 0 tries to get both locks before she makes a round */  
        if(index==0) {
            /*Your code here */
            if (pthread_mutex_lock(&B0) == 0) {
                if (pthread_mutex_lock(&B1) == 0) {
                    numRounds[index]++;
 
                    // unlock both locks
                    pthread_mutex_unlock(&B0);  
                    pthread_mutex_unlock(&B1);  
                }
            }
        }

        /* RACER 1 tries to get both locks before she makes a round */  
        if(index==1) {
            /*Your code here */	
            if (pthread_mutex_lock(&B0) == 0) {
                if (pthread_mutex_lock(&B1) == 0) {
                    numRounds[index]++;
 
                    // unlock both locks
                    pthread_mutex_unlock(&B0);  
                    pthread_mutex_unlock(&B1);  
                }
            }
        } 
    }
    pthread_exit(0);  
} 
