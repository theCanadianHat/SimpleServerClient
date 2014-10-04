// client and server header
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

//global prototypes
void error(char *msg,int en);

//client prototypes//
//writes byte b to file socketfd, returns 1 on success and -1 on error
int L1_write(int socketfd, char b);

//sends a line starting at the address specified by the second parameter
//(line) to the socket specified by sockfd
int L2_write(int sockfd,char *line);

//sends the content of a file specified by filename to the socket specifed
//by sockfd
int L3_write(int sockfd,char *filename);

//server prototypes//
//reads one byte and copies the byte to the address specified
int L1_read(int sockfd, char *b);

//reads a line form teh socket specified by sockfd, and reverses the
//recieved line and stores it in memory starting at the address specifed
//by the pointer *line
int L2_read(int sockfd,char **line);

//reads lines from the socket and prints out the reversed lines
int L3_read(int sockfd);
