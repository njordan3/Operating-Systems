/* client.c   */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> /* provides access to the POSIX (Portable OS Interface) tools */
#include <sys/types.h> /* contains definitions of data types used in system calls */
#include <sys/socket.h> /* includes definitions of structures needed for sockets */ 
#include <netinet/in.h> /* contains constants and structures needed for Internet domain addresses */
#include <netdb.h> /* definitions for network database operations */ 

void error(const char *msg)
{
    perror(msg); /* if system call fails displays a message from stderr and aborts the program.*/
    exit(0);     /* more info in "man perror" */
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n; /* sockfd and portno to store the values returned */
    struct sockaddr_in serv_addr; /* structures defined in the netinet/in.h  */
    struct hostent *server;  /* the hostent structure is defined in netdb.h  */
			     /* hostent defines a host computer on the Internet. */
    char buffer[256]; 
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0); /* more info in "man socket" */
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr)); /* sets all values in a buffer to zero."man bzero" */
    serv_addr.sin_family = AF_INET; /* serv_addr is a structure of type struct sockaddr_in */
	/* AF_INET is to set the type of addresses that the socket can communicate with (in this case IPv4 addresses). */
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length); /* copy byte sequence. "man bcopy" */
    serv_addr.sin_port = htons(portno); /* "man htons" */
    /* copying the port number but first is converted to network byte order using the function htons() */ 
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    printf("Please enter the message: ");
    bzero(buffer,256);  /* sets all values in a buffer to zero. "man bzero" */
    fgets(buffer,255,stdin); /* "man fgets" */
    n = write(sockfd,buffer,strlen(buffer)); /* more info in "man write" */
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,256); 
    n = read(sockfd,buffer,255); 
    if (n < 0)   
         error("ERROR reading from socket");
    printf("%s\n",buffer);
    close(sockfd);
    return 0;
}
