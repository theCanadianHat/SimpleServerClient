#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include "CS.h"

int main(int argc, char *args[]){
  int sockfd, newsockfd, portno, clilen,n;
  char buffer[256];
  struct sockaddr_in serv_addr, cli_addr;
  
  if(argc < 2){
    fprintf(stderr,"ERROR no port provided\n");
    exit(1);
  }
  sockfd = socket(AF_INET,SOCK_STREAM,0);
  if(sockfd<0){
    error("ERROR opening socket",-4);
  }
  bzero((char *)&serv_addr,sizeof(serv_addr));
  portno = atoi(args[1]);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);
  if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0){
    error("ERROR on binding",-5);
  }
  listen(sockfd,5);
  clilen = sizeof(cli_addr);
  newsockfd = accept(sockfd,(struct sockaddr *)&cli_addr,&clilen);
  if(newsockfd<0){
    error("ERROR on accept",-6);
  }
  bzero(buffer,256);
  //n = read(newsockfd,buffer,255);
  char **c;
  *c = buffer;
  n = L3_read(newsockfd);
  if(n<0) error("ERROR reading from socket",-7);
  //printf("Here is the message: %s\n",*c);
  n = write(newsockfd,"I got your message",18);
  if(n<0) error("ERROR writing to socket",-8);
  /*while( n = L2_read(newsockfd,c) ){
    if(n<0) error("ERROR reading from socket",-7);
    printf("Here is the message: %s\n",*c);
    n = write(newsockfd,"I got your message",18);
    if(n<0) error("ERROR writing to socket",-8);
  }*/
  //close(sockfd);
  close(newsockfd);
  return 0;
}
