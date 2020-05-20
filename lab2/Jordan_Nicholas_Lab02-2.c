/*
CMPS 3600 OS
Jordan Nicholas
Lab 02
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static int alarm_fired = 0;
static int alarm_count = 0;

void handler(int signum) //SIGALRM handler
{
	printf("Hello World!\n");
	alarm_fired = 1;
    alarm_count++;
}
void handler2(int signum) //SIGINT handler
{
    printf("\nNumber of alarms delivered: %i\n", alarm_count);
    exit(1); //exit after printing
}

int main(int argc, char *argv[])
{
	signal(SIGALRM, handler); //register handler to handle SIGALRM
    signal(SIGINT, handler2); // register handler to handle SIGINT
	while (!alarm_fired) {
		alarm(1); //Schedule a SIGALRM for 1 second
		sleep(5); // waiting for signal to be delivered
		if (alarm_fired) {
			printf("Turing was right!\n");
			alarm_fired = 0;
		}
	}
	return 0;
}
