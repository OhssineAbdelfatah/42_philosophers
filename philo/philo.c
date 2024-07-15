#include"philo.h"

int main(int ac , char *av[])
{
   if(ac == 6 || ac == 5){
        t_in *in;
        in = (t_in *)malloc(sizeof(t_in));
        if(parse_input(av, in, ac) == -1) // number of meals included
        {
            printf("Error\n");
            return 0;
        }
        print_input(*in); // print input
        philo(in);
   }
   else {
        printf("./philo philos die eat sleep [meals]\n");
   }
    return 0;
}

// void init_

void *philos_routine(void *data)
{
    t_philo *this_philo;

    this_philo = (t_philo *)data;
    //  think sleep eat
    while(1)
    {
        think(this_philo);
        sleeep(this_philo);
    }
    return NULL;
}

int philo(t_in *input)
{
    int  i ;
    t_philo **philo;
    pthread_mutex_t *print;
    pthread_mutex_t *sleep;
    print = malloc(sizeof(pthread_mutex_t));
    sleep = malloc(sizeof(pthread_mutex_t));

    pthread_mutex_init(print ,NULL);
    pthread_mutex_init(sleep ,NULL);
    philo = (t_philo **)malloc(sizeof(t_philo*) * input->num_philo );
    if(!philo)
        return -1;
    i = -1;
    while(++i < input->num_philo){
        philo[i] = (t_philo *)malloc(sizeof(t_philo));
        if(!philo[i])
            return -1;
        
        philo[i]->input = input ;
        philo[i]->id = i +1 ;
        philo[i]->print = print ;
        philo[i]->sleep = sleep ;

    }
    i = -1;

    my_gettime(&(input->start_time));
    while(++i < input->num_philo){
        if(pthread_create( &(philo[i]->thread) , NULL, philos_routine, philo[i])!= 0)
            return -1;
    }
    i = -1;
    while(++i < input->num_philo){
        if(pthread_join( philo[i]->thread , NULL) != 0)
            return -1;
    }
    return 0;
}
