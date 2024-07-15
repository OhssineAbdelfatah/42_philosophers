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
            printf("Error\n");
            return 0;
        }
        // main entry
        print_input(in);
        philo(&in);
        // printf("philo  %d\ndie    %d ms\neat    %d ms\nsleep  %d ms\n[meals %d]\n",in.num_philo,in.t_die,in.t_eat,in.t_sleep,in.meals);
   }
   else {
        printf("Error nbr args\n");
   }
    return 0;
}

// void init_

int philo(t_in *input)
{
    t_philo **philo;
    int  i ;

    philo = (t_philo **)malloc(sizeof(t_philo*) * input->num_philo );
    if(!philo)
        return -1;
    i = -1;
    while(++i < input->num_philo)
    {
        philo[i]->id = i +1 ;
        // philo[i]->input = input;
        if(pthread_create( philo[i]->thread , NULL, philos_routine, philo[i]) == -1)
            return -1;
    }
    return 0;
}

void *philos_routine(void *data)
{
    t_philo *this_philo;

    this_philo = (t_philo *)data;
    //  cycle of life

    // think
    //think(this_philo);
    
    //  sleep
    //  eat
    return NULL;
}
//!!!!!!!!!!!!!!!!!! AFTER YOU FINICH DELETE THE _ IN MAIN ABOVE !!!!!!!!!!!!!!!!
/* 
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
} */