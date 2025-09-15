#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
void forkexample(){
  pid_t p;
  p=fork();
  if(p<0){
    perror("fork failed");
    exit(1);
  }
else if(p==0){
printf("hello from child !");
  }
  else{
  printf("hello from parent !\n");
}
}
int main(){
  forkexample();
return 0;
}
