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


static int	space_sign(const char *s, int *sign)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] == 32 || (s[i] < 14 && s[i] > 8)))
		i++;
	if (s[i] && (s[i] == '-' || s[i] == '+'))
	{
		if (s[i] == '-')
			*sign *= (-1);
		i++;
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	result;
	unsigned long long	temp;

	result = 0;
	sign = 1;
	i = space_sign(str, &sign);
	while (str[i] <= '9' && str[i] >= '0')
	{
		temp = result;
		result = result * 10 + str[i] - 48;
		if (temp != result / 10 && sign == -1)
			return (0);
		else if (temp != result / 10 && sign == 1)
			return (-1);
		i++;
	}
	return ((int)result * sign);
}