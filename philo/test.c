#include<stdio.h>
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
		printf("temp %llu, result %llu\n",temp,result);
		if (result > __INT32_MAX__)
			return (-1);
		i++;
	}
	return ((int)result );
}
int main(){
    printf("%d \n",ft_atoi("2147483648") );
}