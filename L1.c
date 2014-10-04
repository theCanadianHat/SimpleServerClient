//L1.c
#include "CS.h"
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>

void error(char *msg,int en){
  perror(msg);
  exit(en);
}

int L1_write(int socketfd, char b){
  int error = 0;
  printf("L1_write:About to write %c NJH\n",b);
  if( b != '\0' ){
    if( (error=write(socketfd,&b,sizeof(char)))<=0){
      //EOF
      if(error==0){
        printf("L1_write: returning 0\n");
        return error;
      } 
      return(error);
    }
    return error;
  }
  //char nl = '\n';
  //error = write(socketfd,&nl,sizeof(char));
  return -1;
}

int L1_read(int sockfd, char *b){
  int error=0;
  printf("about to read...\n");
    if( (error=read(sockfd,b,sizeof(char))) <= 0){
      if(*b == '\0') error = 0;
      printf("L1_read(while):b: %c NJH\n",*b);
      printf("L1_read(while):error: %i \n",error);
      //EOF
      if(error==0){
        printf("L1_write: returning 0\n");
        return error;
      }
      return(error);
    }
  printf("L1_read:read: %c NJH\n",*b);
  return(error);
}

