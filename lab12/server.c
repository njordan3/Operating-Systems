/* CMPS 3600 OS
 * Lab Assignment 12
 * Jordan Nicholas
 */

/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> /* provides access to the POSIX (Portable OS Interface) tools */
#include <sys/types.h> /* contains definitions of data types used in system calls */
#include <sys/socket.h> /* includes definitions of structures needed for sockets */
#include <netinet/in.h> /* contains constants and structures needed for Internet domain addresses */ 

void error(const char *msg)
{
    perror(msg); /* if system call fails displays a message from stderr and aborts the program.*/
    exit(1);     /* more info in "man perror" */
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno; /* sockfd and newsockfd to store the values returned */
    socklen_t clilen;  /* socklen_t is defined in socket.h, to set the size of address */
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr; /* structs defined in in.h */
    int n;
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);  /* more info in "man socket" */
    if (sockfd < 0) 
        error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr)); /* sets all values in a buffer to zero."man bzero" */
    portno = atoi(argv[1]);   /* ASCII to Integer conversion */
    serv_addr.sin_family = AF_INET; /* serv_addr is a structure of type struct sockaddr_in */
    /* AF_INET is to set the type of addresses that the socket can communicate with (in this case IPv4 addresses). */
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);  /* "man htons" */
    /* copying the port number but first is converted to network byte order using the function htons() */
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) /* bind a name to a socket. "man bind" */
        error("ERROR on binding");
    listen(sockfd,5);
    while(1) {
        clilen = sizeof(cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen); /* "man accept" */
        /* accept/reject jobs sent to a destination */
        if (newsockfd < 0) 
            error("ERROR on accept");
        else
            bzero(buffer,256); /* sets all values in a buffer to zero."man bzero" */
        n = read(newsockfd,buffer,255); /* read from a file descriptor. "man read" */
        if (n < 0)
            error("ERROR reading from socket");
        printf("Here is the message: %s\n",buffer); 
        n = write(newsockfd,"I got your message",18); 
        if (n < 0)
            error("ERROR writing to socket");
    }
    close(sockfd);
    close(newsockfd);
    return 0; 
}
