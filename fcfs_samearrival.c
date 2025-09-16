#include<stdio.h>
void findwaitingtime(int processes [],int n,int bt[],int wt[]){
    wt[0]=0;
    for(int i=1;i<n;i++){
        wt[i]=bt[i-1]+wt[i-1];
    }
}
void findturnaroundtime(int processes[],int n,int bt[],int wt[],int tat[]){
    for(int i=0;i<n;i++){
        tat[i]=bt[i]+wt[i];
    }
}
void findavgtime(int processes[],int n,int bt[]){
    int wt[n],tat[n],total_wt=0,total_tat=0;
    findwaitingtime(processes,n,bt,wt);
    findturnaroundtime(processes,n,bt,wt,tat);
    printf("processes    Burst time    Waiting time    Turn around time\n");
    for(int i=0;i<n;i++){
        total_wt+=wt[i];
        total_tat+=tat[i];
        printf("     %d",(i+1));
        printf("          %d ",bt[i]);
        printf("             %d ",wt[i]);
        printf("                   %d\n",tat[i]);
    }
    float s=(float)total_wt/(float)n;
    float t=(float)total_tat/(float)n;
    printf("average waiting time =%f",s);
    printf("\n");
    printf("average turn around time=%f",t);
}
int main(){
    int n;
    int processes[n];
    printf("enter no of processes :\n");
    scanf("%d",&n);
    int bt[n],wt[n],tat[n];
    printf("enter burst time for each process\n");
    for(int i=0;i<n;i++){
        printf("process %d ", (i+1) );
        scanf("%d",&bt[i]);
    }
    findavgtime(processes, n,  bt);
    return 0;
}
