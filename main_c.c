#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "CS.h"

int main(int argc, char *argv[]){
  int sockfd, portno, n;
  struct sockaddr_in serv_addr;
  //struct hostent *server;

  char buffer[256];
  if(argc < 4){
    fprintf(stderr,"usage %s hostname port\n",argv[0]);
    exit(0);
  }
  portno = atoi(argv[2]);
  sockfd = socket(AF_INET, SOCK_STREAM,0);
  if(sockfd < 0){
    error("ERROR opening socket",-4);
  }
  int ip = inet_aton(argv[1],&serv_addr.sin_addr);
  if(ip == 0){
    error("ERROR with IP",-5);
  }
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(portno);
  if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0){
    error("ERROR connecting",-6);
  }
  //printf("Please enter the message: ");
  bzero(buffer,256);
  //fgets(buffer,256,stdin);

 // char c=fgetc(stdin);
  //n = write(sockfd,buffer,256);
  //n = L2_write(sockfd,buffer);
  //int fd = open(argv[3],O_RDONLY,S_IREAD|S_IWRITE);
  //int nbytes = read(fd,buffer,sizeof(buffer));
  /*FILE * file = fopen(argv[3],"r");
  if(file == NULL) printf("ERROR opening file!!!\n");
  while( fgets(buffer,256,file) != NULL){
    //n = L3_write(sockfd,argv[3]);
    
    bzero(buffer,256);
  }*/
  n = L3_write(sockfd,argv[3]);
  //n = L2_write(sockfd,buffer);
  if(n < 0){
    error("ERROR writing to socket",-7);
  }
  bzero(buffer,256);
  n = read(sockfd,buffer,255);
  if(n<0){
    error("ERROR reading from socket",-8);
  }
  printf("%s\n",buffer);
  close(sockfd);
  printf("SOCKET CLOSED!!!\n");
  return 0;
}
