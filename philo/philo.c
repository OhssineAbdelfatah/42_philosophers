#include"philo.h"

int main_(int ac , char *av[])
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
        // printf("philo  %d\ndie    %d ms\neat    %d ms\nsleep  %d ms\n[meals %d]\n",in.num_philo,in.t_die,in.t_eat,in.t_sleep,in.meals);
   }
   else {
        write(1 , &"Error nbr args\n", 20);
   }
    return 0;
}

int philo(t_in in)
{
    pthread_t philos[in.num_philo];

    int  i ;

    i = -1;
    while(++i < in.num_philo)
        pthread_create( philos + i, NULL, philos_routine, ((void *)(&i)));

    i = 0;
    while(i < in.num_philo)
    {
        pthread_join( philos[i], NULL);
        i++;
    }
    return 0;
}

void *philos_routine(void *data)
{
    int *i;
    i = (int *)data;
    usleep(1000);
    printf("thread %d\n",*i);
    return NULL;
}
//!!!!!!!!!!!!!!!!!! AFTER YOU FINICH DELETE THE _ IN MAIN ABOVE !!!!!!!!!!!!!!!!

void *make_coffe(void *data)
{
    (void )data;
    printf("barista is making coffe ...\n");
    sleep(2);
    printf("coffe is ready.\n");
    return NULL;

}

int main()
{
    pthread_t barista_1[500];

    for(int  i =0 ; i < 500 ; i++){
        pthread_create(i + barista_1 , NULL,   make_coffe, NULL);
    }


    for(int  i =0 ; i < 500 ; i++){
        pthread_join(barista_1[i] , NULL);
    }
}