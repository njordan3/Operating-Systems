/* 
 *   Base file
 */
#include <stdlib.h> 
#include <stdio.h>    
#include <ctype.h>    
#include <unistd.h>   
#include <sys/stat.h>
#include <string.h>

void DisplayUsage(char *);

/*************************
 *       main()          *
 *************************/
int main(int argc, char **argv) {

  int c, i;
  int fileCount = 0;
  //to verify the ownership of a file
  // check: "man getuid"

  struct stat fileStat;
  mode_t addPermissions = 0;
  mode_t removePermissions = 0;;

  c = getopt (argc, argv, "u:g:o:U:G:O:");
  //check: "man getopt"
  if (c == 'g') {
        for (i=0; i < strlen(optarg); i++) {
        if (optarg[i] == 'r') //check: "man optarg"
          addPermissions |= S_IRGRP; //man fstat 
        else if (optarg[i] == 'w')   //man umask
          addPermissions |= S_IWGRP; //man chmod
        else if (optarg[i] == 'x')   //man creat
          addPermissions |= S_IXGRP; //man fopenq
        } 
  } 
  if (c == 'G') {
        for (i=0; i < strlen(optarg); i++) {
        if (optarg[i] == 'r') //check: "man optarg"
          removePermissions |= S_IRGRP; //man fstat 
        else if (optarg[i] == 'w')   //man umask
          removePermissions |= S_IWGRP; //man chmod
        else if (optarg[i] == 'x')   //man creat
          removePermissions |= S_IXGRP; //man fopenq
        } 
  } 
  printf("%04o\n", addPermissions);
  printf("%04o\n", ~addPermissions);
     
 // Change permissions
 // here we can use optind
  stat(argv[3], &fileStat);
  fileStat.st_mode |= addPermissions;
  fileStat.st_mode ^= removePermissions;
  chmod(argv[3], fileStat.st_mode);
 //check: "man optind" 

  return 0;
}

/************************
 *    DisplayUsage()    *
 ************************/
void DisplayUsage(char *programName) {
  
}

//   ./mytestW -g x file1
