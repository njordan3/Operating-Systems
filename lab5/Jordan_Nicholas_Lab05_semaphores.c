/*
 * CMPS3600
 * Lab05: Threads Creation and Execution
 * Jordan Nicholas
 */
/* 
   Multithreaded C Program Using the Pthread API 
   Compile with:
   gcc semaphores_01.c -o semaphores_01 -pthread


   The output must be synchronized to go out in order from case 0 to case 6 using only
   semaphores. You should not change the values in the global array nor use any delays 
   (like sleep()) to achieve the proper output.
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 
# include <pthread.h>
#include <semaphore.h>

void *output(void *arg);

int code[] = { 4, 6, 3, 1, 5, 0, 2 };

sem_t mysemap[8];

int main()
{
    int init = 1;

    for (int i = 0; i < 8; i++) {
        if (sem_init(&mysemap[i], 0, init)) {
            printf("Semaphore was not initialized correctly...\n");
            exit(1);
        } else {
            init = 0;
        }
    }
    
    pthread_t tid[7];

    for (int i = 0; i < 7; i++) {
        pthread_create(&tid[i], NULL, output, (void*)&code[i]);
    }

    for (int i = 0; i < 8; i++) {
        sem_destroy(&mysemap[i]);
    }
//the last semaphore must be unlocked before the main program terminates
    sem_wait(&mysemap[7]);
    return 0;
}

//each thread unlocks another thread so that the output is displayed in the right order
void *output(void *arg)
{
    int n = *(int*)arg;

    switch (n)
    {
        case 0:
            sem_wait(&mysemap[0]);
            printf("\na) A semaphore S is an integer-valued variable which can take only non-negative\n");
            printf("   values. Exactly two operations are defined on a semaphore:\n\n");
            sem_post(&mysemap[1]);
            pthread_exit(0);
            break;

        case 1:
            sem_wait(&mysemap[1]);
            printf("b) Signal(S): If there are processes that have been suspended on this semaphore,\n");
            printf("   wake one of them, else S := S+1.\n\n");
            sem_post(&mysemap[2]);
            pthread_exit(0);
            break;

        case 2:
            sem_wait(&mysemap[2]);
            printf("c) Wait(S):   If S>0 then S:=S-1, else suspend the execution of this process.\n");
            printf("   The process is said to be suspended on the semaphore S.\n\n");
            sem_post(&mysemap[3]);
            pthread_exit(0);
            break;

        case 3:
            sem_wait(&mysemap[3]);
            printf("d) The semaphore has the following properties:\n\n");
            sem_post(&mysemap[4]);
            pthread_exit(0);
            break;

        case 4:
            sem_wait(&mysemap[4]);
            printf("1. Signal(S) and Wait(S) are atomic instructions. In particular, no\n");
            printf("   instructions can be interleaved between the test that S>0 and the\n");
            printf("   decrement of S or the suspension of the calling process.\n\n");
            sem_post(&mysemap[5]);
            pthread_exit(0);
            break;

        case 5:
            sem_wait(&mysemap[5]);
            printf("2. A semaphore must be given an non-negative initial value.\n\n");
            sem_post(&mysemap[6]);
            pthread_exit(0);
            break;

        case 6:
            sem_wait(&mysemap[6]);
            printf("3. The Signal(S) operation must waken one of the suspended processes. The\n");
            printf("   definition does not specify which process will be awakened.\n\n");
            sem_post(&mysemap[7]);
            pthread_exit(0);
            break;
    }
}

