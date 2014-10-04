//L3.c
#include "CS.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <strings.h>
#include <stdio.h>

int L3_write(int sockfd,char *filename){
  char big_buf[256];
  char lil_buf;
  bzero(big_buf,256);
  int file = open(filename,O_RDONLY);
  
  int nlines=0,i=0;
  while( read(file,&lil_buf,sizeof(lil_buf)) !=0 ){
    //printf("L3_write:buffer: %c NJH\n",lil_buf);
    big_buf[i++] = lil_buf;
    if(lil_buf=='\n'){
      //printf("big_buf: %s NJH\n",big_buf);
      if(L2_write(sockfd,&big_buf[0])<0){
        return -1;
      }
      i=0;
      nlines++;
    }
  }
  return nlines;
}

int L3_read(int sockfd){
  char buffer[256];
  //printf("L3_read:buffer(b4 bzero): %s \n",buffer);
  bzero(buffer,256);
  //printf("L3_read:buffer(after bzero): %s \n",buffer);
  char *buf;
  int nbytes=0,e=0,x=0,nlines=0;
  //printf("L3_read:just before while loop\n");
  while( (nbytes = L2_read(sockfd,&buf)) >0 ){
    //if(error == 0)break;
    printf("L3_read:inside L2 while: buffer: %s NJH\n",buf);
    //printf("L3_read:sizeof(buf): %u \n",(unsigned)sizeof(buf));
    if(nbytes > 0){
      buffer[0] = buf;
      printf("L3_read: nbytes > 0: buffer: %s NJH\n",buffer);
      printf("L3_read: nbytes > 0: nbytes = %d \n",nbytes);
      for(e;e<nbytes;e++){
	printf("L3_read: about to write : buffer[%d] = %c njh\n",e,buffer[e]);
        x = write(STDOUT_FILENO,&buffer[e],sizeof(char));
        if(buffer[e] == '\n'){
          printf("L3_read: buffer[%d] == nl : buffer[%d] = %c njh\n",e,e,buffer[e]);
          break;
        }
        if(x<0){
          printf("ERROR: L3_write : writing %c \n",buffer[e]);
          return -1;
        }
      }
      printf("L3_read: under for loop : e = %d \n",e);
      e=0;
      nlines++;
      printf("L3_read: before bzero : buffer = %s njh\n",buffer);
      bzero(&buffer[0],256);
      printf("L3_read: after bzero : buffer = %s njh\n",buffer);
    }
  }
  printf("L3_read: about to return : nlines = %i njh\n",nlines);
  return nlines;
}


