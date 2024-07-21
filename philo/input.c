#include"philo.h"

void error_exit(const char*str)
{
	printf("%s",str);
	exit(EXIT_FAILURE);
}

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


void parse_input(char **input )
{
    int i ;

    i = 0 ;
    while(input[++i])
    {
        if(is_digit(input[i]) == -1 || ft_atoi(input[i]) == -1)
            error_exit("Error\n");
    }
	if(ft_atoi(input[2]) < 60 || ft_atoi(input[3]) < 60 
	|| ft_atoi(input[4]) < 60 || ft_atoi(input[1]) > 200 )
		error_exit("Error\n");
    return ;
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

void print_input(t_table table){
	printf("\n-------------------------------\n");
	printf("number of philos %d\n",table.num_philo);
	printf("time to die      %d\n",table.t_die);
	printf("time to eat      %d\n",table.t_eat);
	printf("time to sleep    %d\n",table.t_sleep);
	printf("number of meals  %d\n",table.meals);
	printf("-------------------------------\n\n");
}