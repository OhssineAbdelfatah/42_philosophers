#include"philo.h"

int is_digit(char *str)
{   
    int i  ;

    i = -1 ;
    while(str[++i])
    {
        if(str[i] > '9' || str[i] < '0')
            return -1 ;
    }
    return 0;
}

int parse_input(char **input ,t_in *in ,int ac)
{
    int i ;

    i = 0 ;
    while(input[++i])
    {
        if(is_digit(input[i]) == -1)
            return -1;
        // convert the string to number
    }
    in->num_philo = ft_atoi(input[1]);
    in->t_die = ft_atoi(input[2]);
    in->t_eat = ft_atoi(input[3]);
    in->t_sleep = ft_atoi(input[4]) ;
    in->meals  = 0;
    if(ac == 6)
        in->meals  = ft_atoi(input[5]);
    return 0;
}