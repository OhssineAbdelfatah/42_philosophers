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
    if(ac == 6)
        in->meals  = ft_atoi(input[5]);
    else 
        in->meals  = 0;
    return 0;
}

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
        printf("ph %d \n",in.num_philo);
        printf("die %d \n",in.t_die);
        printf("eat %d \n",in.t_eat);
        printf("sleep %d \n",in.t_sleep);
        printf("meals %d \n",in.meals);
   }
   else {
        write(1 , &"Error nbr args\n", 20);
   }
    return 0;
}