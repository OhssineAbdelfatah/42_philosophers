#include"philo.h"

int main(int ac , char *av[])
{
    //           0      1                       2          3             4            [5]
   // input : ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
   if(ac == 6 || ac == 5){
        t_in in;
        // number of meals included
        if(parse_input(av, &in, ac) == -1)
        {
            printf("inputs error \n");
            return 0;
        }

        // main entry
        philo(in);
        printf("philo  %d\ndie    %d ms\neat    %d ms\nsleep  %d ms\n[meals %d]\n",in.num_philo,in.t_die,in.t_eat,in.t_sleep,in.meals);
   }
   else {
        write(1 , &"Error nbr args\n", 20);
   }
    return 0;
}

int philo(t_in in)
{
    pthread_t *philos[in.num_philo];

    int  i ;

    i = 0;
    while(i < in.num_philo)
    {
        pthread_create( *(philos+i), NULL, philos_routine, ((void *)(&i)));
        i++;
    }

    i = 0;
    while(i < in.num_philo)
    {
        pthread_join( *philos[i], NULL);
        i++;
    }
    return 0;
}

void *philos_routine(void *data)
{
    int *i;
    i = (int *)data;
    printf("thread %d",*i);
    usleep(10);
    return NULL;
}
//!!!!!!!!!!!!!!!!!! AFTER YOU FINICH DELETE THE _ IN MAIN ABOVE !!!!!!!!!!!!!!!!

/* void *make_coffe(void *data)
{
    (void )data;
    printf("barista is making coffe ...\n");
    sleep(2);
    printf("coffe is ready.\n");
    return NULL;

}

int main()
{
    pthread_t barista_1;
    pthread_t barista_2;

    pthread_create(&barista_1 , NULL,   make_coffe, NULL);
    printf("%ld \n",barista_1->__sig);
    pthread_create(&barista_2 , NULL,   make_coffe, NULL);
    sleep(5);
} */