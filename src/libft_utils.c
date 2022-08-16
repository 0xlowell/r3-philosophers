
#include "philosophers.h"
#include "utils.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (c);
	return (0);
}

int	mem_check(void *ptr)
{
	if (ptr == NULL)
		return (1);
	return (0);
}

long	ft_atol(const char *str)
{
	int		i;
	long	res;
	int		minus;

	minus = 1;
	i = 0;
	res = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		minus = -1;
		i++;
	}
	if (str[i] == '+' && minus == 1)
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + str[i] - '0';
		i++;
	}
	return (res * minus);
}