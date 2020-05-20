#include<stdio.h>
#include<string.h>
#include<semaphore.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

typedef enum dir {North, South, East, West} dir;
typedef struct BAT{
    pthread_t tid;
    dir direction;
    int num;
}BAT;

void manager(); 				
void *crs(BAT*);		
void *leave(BAT*);		
void *arr(BAT*);
int check();
void *proceed(void*);
pthread_mutex_t lock; 		
pthread_cond_t queue[4], begin[4];
int count[4];
const char *myDirections[4] = {"n","s", "e", "w"};
int test_finish = 0;
int test_length = 0;

int main(int argc, char *argv[]){
    int i,l,j;
    BAT *bat;
    if(argc < 2){
        printf("You must add directions\n");
        exit(1);
    }
    pthread_mutex_init(&lock, NULL);
    for( j = 0; j<4; j++){
        count[j] = 0;
    }
    for( j=0; j<4;j++){
        pthread_cond_init(&queue[j],NULL);
    }
    for(j =0; j<4; j++){
        pthread_cond_init(&begin[j],NULL);
    }
    l = strlen(argv[1]);
    test_length = l;
    bat =(BAT*)malloc(l* sizeof(BAT));
    for(i = 0; i<l; i++){
        const char s[] = "nsew";
        bat[i].num = i+1;
        bat[i].direction = strchr(s,argv[1][i]) - s;
        pthread_create(&bat[i].tid,NULL,proceed,(void*) &bat[i]);
    }
    manager();
    for (i = 0; i <l; i++){
        pthread_join(bat[i].tid,NULL);
    }
    for (i = 0; i <4; i++){
        pthread_cond_destroy(&begin[i]);
    }
    for(i =0 ; i<4; i++){
        pthread_cond_destroy(&queue[i]);
    }
    pthread_mutex_destroy(&lock);
    free(bat);
    return(0);
}

void *arr(BAT *b){
    pthread_mutex_lock(&lock);
    count[b->direction]++;
    if(count[b->direction] > 1){
        printf("BAT %d from %s arrives at crossing and waiting\n", b->num, myDirections[b->direction]);
        pthread_cond_wait(&queue[b->direction], &lock);
    }
    else{
        printf("BAT %d from %s arrives at crossing\n", b->num, myDirections[b->direction]);
    }
    pthread_mutex_unlock(&lock);
}

void *crs(BAT *b){
    pthread_mutex_lock(&lock);
    if(count[(b->direction +1) %4] >0 || count[(b->direction +2) %4] > 0 || count[(b->direction +3) %4] >0)
    {
        printf("BAT %d from %s waiting on traffic from %s\n", b->num, myDirections[b->direction],myDirections[(b->direction +1) %4]);
        pthread_cond_wait(&begin[b->direction], &lock);
    }
    sleep(1);
    pthread_mutex_unlock(&lock);
}

void *leave(BAT *b){
    pthread_mutex_lock(&lock);
    printf("BAT %d from %s leaving\n", b->num,myDirections[b->direction]);
    count[b->direction]--;
    if(count[(b->direction+1)%4]>0 || count[(b->direction+2)%4] >0 || count[(b->direction+3)%4]>0)
    {
        pthread_cond_signal(&begin[(b->direction+1) %4]);
    }
    pthread_cond_signal(&queue[b->direction %4]);
    pthread_mutex_unlock(&lock);
    test_finish++;
}

int check(){
    int finish = 0;
    sleep(1);
    pthread_mutex_lock(&lock);
    if(count[0] > 0 && count[1] >0){
        printf("DEADLOCK: BAT jam detected, signaling BAT from north to go\n");
        pthread_cond_signal(&begin[0]);
    }
    else if(count[0] > 0 &&count [2] >0){
        
        printf("DEADLOCK: BAT jam detected, signaling BAT from north to go\n");
        pthread_cond_signal(&begin[0]);
    }
    else if(count[0] > 0 &&count [3] >0){
        
        printf("DEADLOCK: BAT jam detected, signaling BAT from north to go\n");
        pthread_cond_signal(&begin[0]);
    }
    else if(count[1] > 0 &&count [2] >0){
        
        printf("DEADLOCK: BAT jam detected, signaling BAT from north to go\n");
        pthread_cond_signal(&begin[1]);
    }
    else if(count[1] > 0 &&count [3] >0){
        
        printf("DEADLOCK: BAT jam detected, signaling BAT from north to go\n");
        pthread_cond_signal(&begin[1]);
    }
    else if(count[2] > 0 &&count [3] >0){
        
        printf("DEADLOCK: BAT jam detected, signaling BAT from north to go\n");
        pthread_cond_signal(&begin[2]);
    }
    else{
        finish =1;
    }
    pthread_mutex_unlock(&lock);
    return(finish);
}

void *proceed(void *arg){
    BAT *bat =(BAT*)arg;
    arr(bat);
    crs(bat);
    leave(bat);
    pthread_exit(0);
}

void manager(){
    int finish =0 ;
    while(test_finish < test_length) {
        //printf("here\n");
        finish = check();
    }
}

