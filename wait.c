#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main(){
    if(fork()==0){
        printf("hello from child\n");
    }else{
        printf("hello from parent\n");
        wait(NULL);
        printf("child has terminated\n");
    }
    printf("bye\n");
    return 0;
}
