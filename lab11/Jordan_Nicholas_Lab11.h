/* CMPS 3600
 * Jordan Nicholas
 * Lab 11
 */

#include <stdlib.h> 
#include <stdio.h>    
#include <ctype.h>    
#include <unistd.h>   
#include <sys/stat.h>
#include <string.h>

int changePermissions(mode_t addPermissions, mode_t removePermissions, int argc, char** argv)
{
	struct stat fileStat;
    for (int i = optind; i <= argc-1; i++) {
        /* test if file exists */
        if (access(argv[i], F_OK) < 0) {
            fprintf(stderr, "%s does not exist in this directory.\n", argv[i]);
            exit(2);
        }
        /* test if user has permissions to chmod */
		stat(argv[i], &fileStat);
		if (fileStat.st_uid != getuid()) {
            fprintf(stderr, "You do not have permissions to change the permissions of %s.\n", argv[i]);
			exit(2);	
		}
		if (addPermissions)
       		fileStat.st_mode |= addPermissions;
		if (removePermissions)
			fileStat.st_mode &= ~removePermissions;
        chmod(argv[i], fileStat.st_mode);
	}
	return 0;
}

void setPermissions(mode_t *addPermissions, mode_t *removePermissions, int argc, char** argv)
{
	int c, i;
	while ((c = getopt(argc, argv, "u:g:o:U:G:O:")) != -1) {
		/* add permissions */
		if (c == 'u') {
			for (i = 0; i < strlen(optarg); i++) {
				if (optarg[i] == 'r')
					*addPermissions |= S_IRUSR;
				else if (optarg[i] == 'w')
					*addPermissions |= S_IWUSR;
				else if (optarg[i] == 'x')
					*addPermissions |= S_IXUSR;
				else {
					fprintf(stderr, "Invalid argument '%s'.\n", optarg);
					fprintf(stderr, "Proper usage: ./mychmod -[u,g,o] [r,x,w] filename\n");
					exit(1);
				}
			}
		}
		if (c == 'g') {
			for (i = 0; i < strlen(optarg); i++) {
				if (optarg[i] == 'r')
					*addPermissions |= S_IRGRP;
				else if (optarg[i] == 'w')
					*addPermissions |= S_IWGRP;
				else if (optarg[i] == 'x')
					*addPermissions |= S_IXGRP;
				else {
					fprintf(stderr, "Invalid argument '%s'.\n", optarg);
					fprintf(stderr, "Proper usage: ./mychmod -[u,g,o] [r,x,w] filename\n");
					exit(1);
				}
			}
		}
		if (c == 'o') {
			for (i = 0; i < strlen(optarg); i++) {
				if (optarg[i] == 'r')
					*addPermissions |= S_IROTH;
				else if (optarg[i] == 'w')
					*addPermissions |= S_IWOTH;
				else if (optarg[i] == 'x')
					*addPermissions |= S_IXOTH;
				else {
					fprintf(stderr, "Invalid argument '%s'.\n", optarg);
					fprintf(stderr, "Proper usage: ./mychmod -[u,g,o] [r,x,w] filename\n");
					exit(1);
				}
			}
		}
        /* remove permissions */
		if (c == 'U') { 
			for (i = 0; i < strlen(optarg); i++) {
				if (optarg[i] == 'r')
					*removePermissions |= S_IRUSR ;
				else if (optarg[i] == 'w')
					*removePermissions |= S_IWUSR;
				else if (optarg[i] == 'x')
					*removePermissions |= S_IXUSR;
				else {
					fprintf(stderr, "Invalid argument '%s'.\n", optarg);
					fprintf(stderr, "Proper usage: ./mychmod -[u,g,o] [r,x,w] filename\n");
					exit(1);
				}
			}
		}
		if (c == 'G') {
			for (i = 0; i < strlen(optarg); i++) {
				if (optarg[i] == 'r')
					*removePermissions |= S_IRGRP;
				else if (optarg[i] == 'w')
					*removePermissions |= S_IWGRP;
				else if (optarg[i] == 'x')
					*removePermissions |= S_IXGRP;
				else {
					fprintf(stderr, "Invalid argument '%s'.\n", optarg);
					fprintf(stderr, "Proper usage: ./mychmod -[u,g,o] [r,x,w] filename\n");
					exit(1);
				}
			}
		}
		if (c == 'O') {
			for (i = 0; i < strlen(optarg); i++) {
				if (optarg[i] == 'r')
					*removePermissions |= S_IROTH;
				else if (optarg[i] == 'w')
					*removePermissions |= S_IWOTH;
				else if (optarg[i] == 'x')
					*removePermissions |= S_IXOTH;
				else {
					fprintf(stderr, "Invalid argument '%s'.\n", optarg);
					fprintf(stderr, "Proper usage: ./mychmod -[u,g,o] [r,x,w] filename\n");
					exit(1);
				}
			}
		}
	}
}
