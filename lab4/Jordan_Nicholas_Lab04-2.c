/*
 * CMPS 3600
 * Jordan Nicholas
 * Lab04-2
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

void handler(int signum)
{
    if (signum == SIGTSTP) {
        printf("Stopping process for 3 seconds...\n");
        sleep(3);
        printf("Continuing process...\n");
        raise(SIGCONT);
    }
}

int main()
{
    signal(SIGTSTP, handler);
    int count_to_stop = 0;
    //print first 10 terms of the fibonacci series
    for (int i = 1; i < 11; i++) {
        sleep(1);
        if (count_to_stop == 5) {
            raise(SIGTSTP);
        }
        count_to_stop++;
        printf("%i\n", fib(i));
    }
    return 0;
}
