#include "../includes/philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->forks[philo->index]);
	print_messages("has taken a fork", philo);
	if (philo->index + 1 == philo->shared->nb_philo)
		pthread_mutex_lock(&philo->shared->forks[0]);
	else
		pthread_mutex_lock(&philo->shared->forks[philo->index + 1]);
	print_messages("has taken a fork", philo);
	print_messages("Is eating", philo);
	philo->shared->last_eat[philo->index] = get_time(philo->shared->start);
	philo->nb_eats++;
	usleep(philo->shared->time_eat);
	pthread_mutex_unlock(&philo->shared->forks[philo->index]);
	print_messages("has drop a fork", philo);
	if (philo->index + 1 == philo->shared->nb_philo)
		pthread_mutex_unlock(&philo->shared->forks[0]);
	else
		pthread_mutex_unlock(&philo->shared->forks[philo->index + 1]);
	print_messages("has drop a fork", philo);
}

void	sleeping(t_philo *philo)
{
	print_messages("is sleeping", philo);
	usleep(philo->shared->time_sleep);
	print_messages("is thinking", philo);
}

int	check_end(t_philo *philo)
{
	if (get_time(philo->shared->start) - philo->shared->last_eat[philo->index] > philo->shared->time_die)
	{
		philo->shared->is_dead = 1;
		print_messages("is dead", philo);
		return (1);
	}
	return (0);
}