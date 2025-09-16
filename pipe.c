#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#define MSGSIZE 100
int main(){
  int fd[2];
char msg[MSGSIZE];
pid_t pid;
if(pipe(fd)==-1){
perror("pipe");
exit(EXIT_FAILURE);
}
pid = fork();
if(pid<0){
perror("fork");
exit(EXIT_FAILURE);
}
  if(pid>0){
close(fd[0]);
    printf("enter a message to send :");
    fgets(msg,MSGSIZE,stdin);
    size_t len=strlen(msg);
    if(len>0 && msg[len-1]=='\n'){
        msg[len-1]='\0';
        len--;
    }
size_t bytes_written=write(fd[1],msg,len+1);
if(bytes_written==-1);{
    perror("write");
exit(EXIT_FAILURE);
}
printf("parent wrote %zd bytes to pipe \n",bytes_written);
close(fd[1]);
wait(NULL);
}else{
    close(fd[1]);
    size_t bytes_read=read(fd[0],msg,MSGSIZE);
    if(bytes_read==-1){
        perror("read");
        exit(EXIT_FAILURE);
    }
    printf("child received message : %s\n",msg);
    printf("child read %zd bytes from pipe \n",bytes_read);
    close(fd[0]);
    exit(EXIT_SUCCESS);
}
    return 0;
}
