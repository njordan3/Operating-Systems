/*
CMPS 3600 OS
Jordan Nicholas
Lab 03
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

static int alarm_fired = 0;
static int alarm_count = 0;

void handler(int signum) //SIGALRM handler
{
	alarm_fired = 1;
    alarm_count++;
}

void handler2(int signum) //SIGFPE handler
{
    printf("FLOATING POINT EXCEPTION!!!!!\n");
    printf("Number of divisions to activate SIGFPE: %i\n", alarm_count);
    raise(SIGQUIT); // activate SIGTERM to end process
}

int main(int argc, char *argv[])
{
	signal(SIGALRM, handler); // register handler to handle SIGALRM
    signal(SIGFPE, handler2); // register handler to handle SIGFPE
    int array1[] = {2, 7, 11, 25, 4};
    int array2[] = {23, 42, 33, 0, 8};
    srand(time(NULL));
	while (!alarm_fired) {
		alarm(1); //Schedule a SIGALRM for 1 second
		sleep(5); // waiting for signal to be delivered
		if (alarm_fired) {
            int random1 = rand() % 5;
            int random2 = rand() % 5;
            printf("dividing %i by %i\n", 
                array1[random1], array2[random2]);
            int result = array1[random1] / array2[random2];
			alarm_fired = 0;
		}
	}
	return 0;
}
