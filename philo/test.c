#include<sys/time.h>
#include<stdio.h>

int main(){

    struct timeval t_time;

    gettimeofday(&t_time,NULL);

    printf("sec %ld usec %d , %lu \n", t_time.tv_sec , t_time.tv_usec,t_time.tv_usec+  t_time.tv_sec * 1000);
}