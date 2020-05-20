/*
 * CMPS 3600
 * Jordan Nicholas
 * Lab01
 */

#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/file.h>

#define BUFSZ 100

/* do this before using buffer for write calls */
void zeroOutBuf(char *str){
	int i;
	for (i=0; i<BUFSZ; i++)
		str[i]=0;
}
int main () {

	int status = 0;
	pid_t parent,cpid;  /* pid_t is POSIX standard for system API */

	/* grab parent's pid */
	parent = getppid(); 

	/* FORK */
	cpid = fork();  
	if (cpid < 0) {
		perror("fork: ");
		exit(0);
	}
	/* CHILD */ 
	if (cpid == 0) { 

		int exitcode = 77;
		char buf[BUFSZ];
		zeroOutBuf(buf);

		/* open a log file */
		int logf;
		logf = open("log", O_WRONLY|O_CREAT|O_TRUNC, 0644);  
		if (logf == -1) 
			perror("File open error: "); 

		/* write info to child's log file */
		time_t timer;
		struct tm *tm_info;
		time(&timer);
		tm_info = localtime(&timer);
		strftime(buf, 26, "%Y:%m:%d %H:%M:%S\n", tm_info);
		write(logf,buf,strlen(buf));
		sprintf(buf,"child's pid: %d\n",getpid()); 
		write(logf,buf,strlen(buf));
		sprintf(buf,"child's exit code: %d\n", exitcode);
		write(logf,buf,strlen(buf));
		close(logf);
		sleep(5);
		exit(exitcode); 
	}

	/* PARENT */
	else {
		char buf[BUFSZ];
		sprintf(buf,"from parent. pid: %d, status: %d\n",parent,status);
		write(1,buf,strlen(buf));
        sleep(5);   
		pid_t pid = waitpid(pid, &status, 0);
        sleep(5);   // sleep to give us time to see the zombie
        if (WIFEXITED(status))
			sprintf(buf,"my child exited with code: %d\n", WEXITSTATUS(status));
		write(1,buf,strlen(buf));

		exit (EXIT_SUCCESS);
	}
	return 0;
}

/* QUESTION 1
When the child terminates before the parent, and the parent does not wait, the
child's status is printed as <defunct>.
*/
