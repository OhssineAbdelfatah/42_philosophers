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

static int init_input(char **arg, t_in **input)
{
	(*input)->num_philo = ft_atoi(arg[1]);
    (*input)->t_die = ft_atoi(arg[2]);
    (*input)->t_eat = ft_atoi(arg[3]);
    (*input)->t_sleep = ft_atoi(arg[4]) ;
    (*input)->meals  = -1;
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
    }
	i = 1;
	while(++i < 5)
	{
		if(ft_atoi(input[i]) == -1)
			return -1;
	}
	init_input(input, &in);
    if(ac == 6 ){
		if( ft_atoi(input[5]) != -1)
        	in->meals  = ft_atoi(input[5]);
		else	
			return -1;
	}
    return 0;
}

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	result;
	unsigned long long	temp;

	result = 0;
	i = 0;
	while (str[i] <= '9' && str[i] >= '0')
	{
		temp = result;
		result = result * 10 + str[i] - 48;

		if (result > 2147483647)
			return (-1);
		i++;
	}
	return ((int)result );
}

void print_input(t_in in){
	printf("\n-------------------------------\n");
	printf("number of philos %d\n",in.num_philo);
	printf("time to die      %d\n",in.t_die);
	printf("time to eat      %d\n",in.t_eat);
	printf("time to sleep    %d\n",in.t_sleep);
	printf("number of meals  %d\n",in.meals);
	printf("-------------------------------\n\n");
}