#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
int main(){
    pid_t pid;
    printf("enter range\n");
    int n,m;
    scanf("%d %d",&n,&m);
    pid=fork();
    if(pid<0){
        printf("fork faild");
        exit(1);
    }
    else if(pid==0){
        printf("child process pid=%d\n",getpid());
        int sumo=0,l;
        if(n%2==0)
            l=n+1;
        else
            l=n;
        for(int i=l;i<=m;i=i+2){
            sumo+=i;
        }
        printf("%d\n",sumo);
    }else{
        printf("parent process pid=%d\n",getpid());
        int sume=0,l;
        if(n%2==0)
            l=n;
        else
            l=n+1;
        for(int i=l;i<=m;i=i+2){
            sume+=i;
        }
        printf("%d\n",sume);
    }
    return 0;
}
