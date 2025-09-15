#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
int main(){
  pid_t p=fork();
  if(p<0){
    perror("fork failed");
    exit(1);
}
printf("hello world !! , process_id(pid)=%d\n",getpid());
return 0;
}
  
