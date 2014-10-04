//L2.c
#include "CS.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int L2_write(int sockfd,char *line){
  printf("L2_write:line: %s NJH \n",line);
  int line_len = strlen(line);
  printf("L2_write:line_len: %d \n",line_len);
  char *line_ptr = line;
  int i=0,e=0,r=0;
  while(1){
    e = L1_write(sockfd,*line_ptr);
    if(*line_ptr == '\n'){
      r++;
      break;
    }
    if(e==-1) return -1;
    if(e==0) break;
    if(e==1){
      r += e;
      line_ptr++;
    }
  }
  if(r != line_len){
    printf("r != line_len, r = %d, line_len = %d\n",r,line_len);
    return -1;
  }
  printf("L2_write: r = %d, line_len = %d \n",r,line_len);
  //int er = L1_write(sockfd,*line_ptr);
  //if(er<0) fprintf(stderr,"ERROR L1_write.2\n");
//  free(line_ptr);
  return r;
}

int L2_read(int sockfd,char **line){
  int i=0,e=0,r=0;
  char b, buffer[256];
  printf("L2_read:just before while loop\n");
  int en = L1_read(sockfd,&b);
  if(en>0){
    if(b == '\n'){
      printf("L2_read.1: b==nl : b = %c njh\n",b);
      buffer[i] = b;
      return 1;
    }
    while(b != '\n'){
      printf("L2_read: b!=nl : b = %c njh\n",b);
      buffer[i] = b;
      en = L1_read(sockfd,&b);
      if(b == '\n'){
	printf("L2_read.2: b==nl : b = %c njh\n",b);
        i++;
        break;
      }
      if(en ==0) break;
      if(en < 0){
        fprintf(stderr,"ERROR: reading in L2_read\n");
        return -1;
      }
      i++;
    }
  }
  i++;
  *line = &buffer[0];
  //buffer[0] = *line;
  printf("L2_read: after while: line = %s njh\n",*line);
  //char *front = *line;
  //char *temp = &buffer[i-1];
  /*for(e;e<i;e++){
    **line = *temp;
    temp--;
    line++;
  }
  **line = '\n';
  *line = front;*/
  printf("L2_read: before return : i = %i njh\n",i);
  return i;
/*  while( e = L1_read(sockfd,buf) != 0 ){
    //printf("L2_read:buf: %c NJH\n",*buf);
    if(*buf == '\n'){
      //printf("if buf == nl\n");
     break;
    }
    if(e==-1){
      //printf("if e == -1\n");
      return -1;
    } 
    if(e==1){
      //printf("if e == 1\n");
      r += e;
      buf++;
    }
  }
  if(e==0){
    //printf("if e == 0\n");
  }
  r++;
  buf = temp;
  int len = 0;
  if(buf != NULL){
    len = strlen(buf);
  }
  //printf("L2_read: r = %d, len = %d \n",r,len);
  //printf("L2_read:line = %s NJH \n",*line);
  //printf("L2_read:buf = %s NJH \n",buf);
  //printf("L2_read:temp = %s NJH \n",temp);
  //int er = L1_read(sockfd,buf);
  //if(er<0) fprintf(stderr,"ERROR L1_read\n");
//  free(buf);
  return (len);*/
}
