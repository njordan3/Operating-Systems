/*
 * CMPS 3600
 * Jordan Nicholas
 * Lab04-1
 */

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

int fib(int n)
{
	if (n < 2)
        return n;
    else
        return fib(n-1) + fib(n-2);
}

int main()
{
	pid_t cpid = fork();

	/* CHILD */
	if (cpid == 0) {
        pid_t ppid = getppid();
        sleep(6);
        printf("Stopping parent process for 3 seconds...\n");
        kill(ppid, SIGSTOP);
        sleep(3);
        printf("Continuing parent process...\n");
        kill(ppid, SIGCONT);
        sleep(6);
		exit(EXIT_SUCCESS);
	}

	/* PARENT */
	else {
        //print first 10 terms of the fibonacci series
		for (int i = 1; i < 11; i++) {
            sleep(1);
            printf("%i\n", fib(i));
        }
        exit(EXIT_SUCCESS);
	}	
	return 0;
}
