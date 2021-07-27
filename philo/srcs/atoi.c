#include "../includes/philo.h"

int	ft_isdigit(int c)
{
	if (c <= '9' && c >= '0')
		return (1);
	return (0);
}

int		ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	else
		return (0);
}

int			ft_atoi(const char *str)
{
	int				i;
	int				j;
	unsigned long	res;
	int				sign;

	sign = 1;
	res = 0;
	i = 0;
	j = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + str[i++] - 48;
		j++;
	}
	if (res > 9223372036854775807 && sign == -1)
		return (0);
	else if (res > 9223372036854775807 && sign == 1)
		return (-1);
	return (res * sign);
}