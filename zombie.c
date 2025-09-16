#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/wait.h>
int main(){
    pid_t p=fork();
    if(p>0){
        printf("envoke parent \n");
        sleep(5);
        wait(NULL);
        int c=0;
        while(c++!=5){
            printf("exit parent\n");
        }
    }
    if(p==0){
        printf("enter child  ");
        printf(" exit child\n");
        exit(0);
    }
    return 0;
}

  
  
