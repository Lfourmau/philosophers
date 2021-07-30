#include "../includes/philo.h"

void	custom_usleep(int reach)
{
	int time;
	struct timeval tmp;

	time = 0;
	gettimeofday(&tmp, 0);
	while (time < reach)
	{
		usleep(20);
		time = get_time(tmp);
	}
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->forks[philo->index]);
	print_messages("has taken a fork", philo, 0);
	pthread_mutex_lock(&philo->shared->forks[philo->place % philo->shared->nb_philo]);
	print_messages("has taken a fork", philo, 0);
	print_messages("is eating", philo, 0);
	gettimeofday(&philo->shared->last_eat[philo->index], NULL);
	custom_usleep(philo->shared->time_eat); //custom_usleep() sinon decalage de ouf
	philo->nb_eats++;
	pthread_mutex_unlock(&philo->shared->forks[philo->index]);
	print_messages("has drop a fork", philo, 0);
	pthread_mutex_unlock(&philo->shared->forks[philo->place % philo->shared->nb_philo]);
	print_messages("has drop a fork", philo, 0);
}

void	sleeping(t_philo *philo)
{
	print_messages("is sleeping", philo, 0);
	custom_usleep(philo->shared->time_sleep); //custom_usleep() sinon decalage de ouf
	print_messages("is thinking", philo, 0);
}

void	track_end(t_philo *philos, t_shared *shared)
{
	int i;

	while (1)
	{
		i = -1;
		while (++i < shared->nb_philo)
		{
			if (get_time(shared->last_eat[i]) > philos->shared->time_die)
			{
				print_messages("is dead", &philos[i], 1);
				exit(1);
			}
		}
	}
}
