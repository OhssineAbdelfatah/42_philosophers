#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<sys/wait.h>


int main(){
    pid_t pid;
    
    printf("fork here : %d\n",getpid());

    pid = fork(); 

    if(pid < 0 )
        printf("fork error");
    printf("fork success \n");
    if(pid == 0){
        printf("Child: I'm the child, my internal pid is %d \n", pid);
        exit(0);
    }
    else if(pid > 0)
        wait();
        printf("Parent: I'm the parent, my child's pid is %d \n", pid);
    return 0;
}

