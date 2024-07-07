#include<stdio.h>

typedef struct person
{
    int age;
    char *name;
    char *adress;
} per;

void make(void *arg){
    char *p;

    p = (char *) arg;
    printf("name : %s, %ld ,%ld\n",p,sizeof(int), sizeof(void *));

    
}



int  main()
{
//     per p1;

//     p1.name = "abde";
//     p1.age = 21 ;
//     p1.adress = "martil , hay ahriq";
// int  i = 1 ;
// void * ii = (void *)i;
    make(&"a");

}