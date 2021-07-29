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

void	print_messages(char *str, t_philo *philo, int is_dead)
{
	pthread_mutex_lock(&philo->shared->speak);
	printf("%d Philo %d %s\n", get_time(philo->shared->start), philo->place, str);
	if (is_dead == 0)
		pthread_mutex_unlock(&philo->shared->speak);
}

int	get_time(struct timeval time_one)
{
	struct timeval time_two;
	long int first_time;
	long int second_time;

	gettimeofday(&time_two, NULL);
	first_time = time_one.tv_sec * 1000 + time_one.tv_usec / 1000;
	second_time = time_two.tv_sec * 1000 + time_two.tv_usec / 1000;
	return (second_time - first_time);
}