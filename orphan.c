#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
int main(){
    pid_t p=fork();
    if(p>0){
        printf("i am parent ");
        sleep(2);
        printf("%d",getpid());
        printf(" terminated\n");
        exit(0);
    }
    if(p==0){
        printf("my child  ");
        sleep(2);
        printf("%d",getpid());
        printf(" terminated\n");
    }
    return 0;
}

