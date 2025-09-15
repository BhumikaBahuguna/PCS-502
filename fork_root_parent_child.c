#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
int main(){
    pid_t pid1,pid2;
    printf("root process started , PID =%d\n",getpid());
    pid1=fork();
    if(pid1<0){
        perror("fork failed");
        exit(1);
    }if(pid1==0){
        printf("child1:PID =%d,parent PID=%d\n",getpid(),getppid());
        pid2=fork();
        if(pid2<0){
            perror("fork 2 failed (in child 1)");
            exit(1);
        }if(pid2==0){
            printf("grandchild (child of child1) , PID =%d,parent PID=%d\n",getpid(),getppid());
        }
    }else{
        pid2=fork();
        if(pid2<0){
            perror("fork 2 failed (in parent)");
            exit(1);
        }if(pid2==0){
            printf("child 2 PID =%d,parent PID=%d\n",getpid(),getppid());
        }
    }
    sleep(1);
    return 0;
}
