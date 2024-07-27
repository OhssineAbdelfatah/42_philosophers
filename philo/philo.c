#include"philo.h"

int main(int ac , char *av[])
{
    t_table table;
   if(ac == 6 || ac == 5){
        // 1 : parse input 
        parse_input(av);
        // 2 : init data 
        init_data(&table, av);

        // 3 : start the simulation 
        start_dinner(&table);
        
        // 4 : init data 
        // clean(&table);
   }
   else {
        printf("./philo philos die eat sleep [meals]\n");
   }
    return 0;
}

void init_table(t_table *table,char **av)
{
    table->num_philo = atoi(av[1]);
    table->t_die = atoi(av[2]);
    table->t_eat = atoi(av[3]);
    table->t_sleep = atoi(av[4]);
    if(av[5])
        table->meals = atoi(av[5]);
    table->stop_state = 0;
    return ;
}

void    init_forks(t_table **table)
{
    int i;

    (*table)->forks = (t_fork *)malloc(sizeof(t_fork)* (*table)->num_philo);
    if(!(*table)->forks)
        return ;
    i = -1;
    while(++i < (*table)->num_philo)
    {
        (*table)->forks[i].id = i;
        (*table)->forks[i].fork = malloc(sizeof(t_mtx));
        pthread_mutex_init(((*table)->forks[i].fork),NULL);
    }
    return ;
}
void    init_philos(t_table **table)
{
    int i ;

   ( *table)->philos = (t_philo *)malloc(sizeof(t_philo) * ( *table)->num_philo );
    if(!( *table)->philos)
        return ;
    i = -1;
    while(++i <(*table)->num_philo){
        ( *table)->philos[i].table = *table ;
        ( *table)->philos[i].last_eat = 0 ;
        ( *table)->philos[i].die_state = 0 ;
        ( *table)->philos[i].meals_counter = 0 ;
        ( *table)->philos[i].id = i +1 ;
    }
    // assing each philo his left and right forks (address of the n and n+1 mutexs)
}

void init_data(t_table *table, char **av)
{

    t_mtx print;
    t_mtx state;

    table->print = malloc(sizeof(t_mtx));
    table->state = malloc(sizeof(t_mtx));
    pthread_mutex_init(&print, NULL);
    pthread_mutex_init(&state, NULL);
    table->print = &print;
    table->state = &state;
    // init table
    init_table(table, av);
    // init philos
    init_philos(&table);
    // init forks
    init_forks(&table);
    // assing forks to philos
    assing_forks(&table);

    return ;
}

void start_dinner(t_table *table)
{
    int  i ;

    table->start_time = my_gettime();
    i = -1;
    while( ++i < table->num_philo){
        if(pthread_create( &(table->philos[i].thread) , NULL, philos_routine, &(table->philos[i])) != 0)
            return ;
    }
    
    // check for dead threads
    i = 0;
    while(!table->stop_state){
        if(my_gettime() - table->philos[i].last_eat > (size_t)table->t_die)
        {
            table->stop_state = 1;
            i = -1 ;
            while(++i < table->num_philo)
                table->philos[i].die_state = 1;
            pthread_mutex_lock(table->print);
            printf(BOLD_RED"%zu"RESET" %d has died\n",my_gettime() - table->start_time ,table->philos[i].id);
            pthread_mutex_unlock(table->print);
            break;
        }
        i++;
    }
        
    // main thread should wait for all the threads
    i = -1;
    while(++i < table->num_philo){
        if(pthread_join( table->philos[i].thread, NULL) != 0)
            return ;
    }
}




void assing_forks(t_table **table)
{
    int i ;

    i = -1;
    while(++i < (*table)->num_philo){
        (*table)->philos[i].right_fork = i ;
        if(i+1 == (*table)->num_philo)
            (*table)->philos[i].left_fork = 0 ;
        else
            (*table)->philos[i].left_fork = i+1 ;
    }
    return ;
}


