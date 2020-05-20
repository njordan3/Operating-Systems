/* Jordan Nicholas
 * CMPS 3600
 * Lab 13
 */
#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h>

int main()
{
	int fd[2]; // Store both ends of the pipe
	if (pipe(fd) == -1) {
		fprintf(stderr, "Pipe Failed");
		exit(1);
	}
	pid_t p = fork();
	if (p > 0) {	// Parent
		char message[10] = "Go to bed!";
		write(fd[1], message, strlen(message));
		wait(NULL);
	} else {		// Child
		char buffer[100];
		read(fd[0], buffer, 100);
		buffer[strlen(buffer)-1] = '\0';	// Null terminate string
		printf("Child receive the message: %s\n", buffer);
		close(fd[0]);	// Close reading end
		close(fd[1]);	// Close writing end
		exit(0);
	}	
	return 0;
}
