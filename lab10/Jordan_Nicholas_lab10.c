/* CMPS 3600
 * Jordan Nicholas
 * Lab10
 */

#include <stdio.h>  
#include <pthread.h> 
#include <stdlib.h> 
#include <stdint.h>
#include <unistd.h>
#include <string.h>

typedef enum route {North, East, South, West} route;
const char* myDirections[4] = {"n", "e", "s", "w"};
/* BAT structure */
typedef struct BAT {
    pthread_t tid;
    int index;
    route direction;
} BAT;
/* BATMAN thread to check for deadlock */
pthread_t batman;
/* mutex lock */  
pthread_mutex_t lock;
/* condition variables for each direction */
pthread_cond_t queue[4], priority[4];
void *Trolley(void*); /* prototype of trolley routine */
void *manager(void*);
void arrive(BAT*);
void leave(BAT*);
void cross(BAT*);
void check();
int count[4];
/* amount of characters in commandline input */
int length = 0;
/* amount of BATs that have left the trolley */
int finish = 0;

int main(int argc, char* argv[])  
{  
    if (argc != 2) {
        printf("You need 2 arguments.\nExample: ./lab10 nsewnse\n");
        exit(1);
    }
    /* get character count of commandline string and test integrity of data */
    for (length; argv[1][length] != '\0'; length++) {
        if (argv[1][length] != 'n' &&
            argv[1][length] != 'e' &&
            argv[1][length] != 's' &&
            argv[1][length] != 'w') {
            printf("Invalid character found!\n");
            exit(1);
        }
    }
	/* create 'length' amount of BATs */
    BAT bat[length];
    /* initialize count and condition variables */
    for (int i = 0; i < 4; i++) {
        if (pthread_cond_init(&queue[i], NULL)) {
            printf("Condition variable, queue, was not initialized correctly...\n");
            exit(1);
        }
        if (pthread_cond_init(&priority[i], NULL)) {
            printf("Condition variable, priority, was not initialized correctly...\n");
            exit(1);
        }
        count[i] = 0;
    }
	/* initialize mutex */
    if (pthread_mutex_init(&lock, NULL)) {
        printf("Mutex lock was not initialized correctly..\n");
        exit(1);
    }
	/* create BATMAN */
	pthread_create(&batman, NULL, manager, (void*)NULL);
	/* create BATs */
    for (int i = 0; i < length; i++) {
        const char* s = "nesw";
        bat[i].index = i + 1;
        bat[i].direction = strchr(s, argv[1][i]) - s;
        pthread_create(&bat[i].tid, NULL, Trolley, (void*)&bat[i]);
    }
	/* wait for threads to join */
    for (int i = 0; i < length; i++) {
        pthread_join(bat[i].tid, NULL);
    }
	pthread_join(batman, NULL);

    printf("\nThere are no more products on the trolley\n");  
    for (int i = 0; i < 4; i++) {
        pthread_cond_destroy(&queue[i]);
        pthread_cond_destroy(&priority[i]);
	}
    pthread_mutex_destroy(&lock);
    return 0;  
}
void *manager(void* arg)
{
	/* keep checking until every BAT has left the trolley */
    while (finish < length) {
    	check();
	}
}
void arrive(BAT* arg)
{
    pthread_mutex_lock(&lock);
    count[arg->direction]++;
	/* check if queue isn't empty */
    if (count[arg->direction] > 1) {
        printf("BAT %d from %s arrives at crossing and waiting\n", arg->index, myDirections[arg->direction]);
        pthread_cond_wait(&queue[arg->direction], &lock);
    } else{
        printf("BAT %d from %s arrives at crossing\n", arg->index, myDirections[arg->direction]);
    }
    pthread_mutex_unlock(&lock);
}
void cross(BAT* arg)
{
	pthread_mutex_lock(&lock);
    if (count[(arg->direction + 1) % 4] > 0 ||
	  	count[(arg->direction + 2) % 4] > 0 ||
	  	count[(arg->direction + 3) % 4] > 0) {
        printf("BAT %d from %s waiting on traffic from %s\n", arg->index,
			myDirections[arg->direction], myDirections[(arg->direction + 1) % 4]);
        pthread_cond_wait(&priority[arg->direction], &lock);
    }
	/* simulate crossing */
    sleep(1);
    pthread_mutex_unlock(&lock);
}
void leave(BAT* arg)
{
    pthread_mutex_lock(&lock);
    printf("BAT %d from %s leaving\n", arg->index, myDirections[arg->direction]);
    count[arg->direction]--;
	/* signal next BAT according to priority */
    if (count[(arg->direction + 1) % 4] > 0 ||
		count[(arg->direction + 2) % 4] > 0 ||
 		count[(arg->direction + 3) % 4] > 0) {
        pthread_cond_signal(&priority[(arg->direction + 1) % 4]);
    }
    pthread_cond_signal(&queue[arg->direction % 4]);
    pthread_mutex_unlock(&lock);
	finish++;
}
void check()
{
	sleep(1);
    if (count[0] > 0 && count[1] > 0){
        printf("DEADLOCK: BAT jam detected, signaling BAT from North to go\n");
    pthread_mutex_lock(&lock);
        pthread_cond_signal(&priority[0]);
    } else if (count[0] > 0 && count[2] > 0) {
        printf("DEADLOCK: BAT jam detected, signaling BAT from North to go\n");
    pthread_mutex_lock(&lock);
        pthread_cond_signal(&priority[0]);
    } else if (count[0] > 0 && count[3] > 0){
        printf("DEADLOCK: BAT jam detected, signaling BAT from North to go\n");
    pthread_mutex_lock(&lock);
        pthread_cond_signal(&priority[0]);
    } else if (count[1] > 0 && count[2] > 0) {
        printf("DEADLOCK: BAT jam detected, signaling BAT from North to go\n");
    pthread_mutex_lock(&lock);
        pthread_cond_signal(&priority[1]);
    } else if (count[1] > 0 && count[3] > 0) {
        printf("DEADLOCK: BAT jam detected, signaling BAT from North to go\n");
    pthread_mutex_lock(&lock);
        pthread_cond_signal(&priority[1]);
    } else if (count[2] > 0 && count[3] > 0) {
        printf("DEADLOCK: BAT jam detected, signaling BAT from North to go\n");
    pthread_mutex_lock(&lock);
        pthread_cond_signal(&priority[2]);
	}
    pthread_mutex_unlock(&lock);
}

void *Trolley(void *arg)  
{
    BAT *data = (BAT*)arg;
    arrive(data);
    cross(data);
    leave(data);
    pthread_exit(0);  
}
