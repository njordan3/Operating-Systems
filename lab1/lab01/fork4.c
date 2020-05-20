/* fork4.c     

  demonstrate how a child becomes an orphan; when the parent dies before 
  harvesting the child's exit code the child becomes an orphan and is 
  inherited by init; init harvests the code (no zombie)

  Compile, execute and view log file:

     $ make  
        OR 
     $ gcc -o fork4 fork4.c
     $ ./fork4
     $ cat log
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

int fib(int n) {
  if (n<2) return n;
  else return fib(n-1) + fib(n-2);
}

int main() {

   int status, ret;
   pid_t cpid,parent;
   parent = getppid();

   cpid = fork();  /* fork returns pid of child to the parent, 0 to child */

   /* CHILD */
   if (cpid == 0) {  /* 0 means you are the child */

      char buf[100];
      int logfd;   
      pid_t me;
      me = getpid();
      parent = getppid();
 
      logfd = open("log", O_WRONLY|O_CREAT|O_TRUNC, 0644);  /* open log */

      /* write pids to log */
      sprintf(buf,"me: %d my parent: %d\n",me,parent); 
      write(logfd,buf,strlen(buf));

      /* child suspends for a few seconds to make sure parent is dead */
      sleep(2); 

      /* grab pids after wait - parent should be init */
      sprintf(buf,"me: %d my parent: %d\n",getpid(),getppid()); 
      write(logfd,buf,strlen(buf));

      /* sync the file or strange things happen when the parent dies */
      fsync(logfd);

      close(logfd);
 
      exit(0); 
   }

   /* PARENT */
   else {

      /* parent does some busy work before dying - long enough for the child to
         write its first entry to log */
      ret = fib(10); /* busy work */
      printf("Parent pid: %d Fib 10: %d\n",parent,ret);

      exit(0);
   }
}
