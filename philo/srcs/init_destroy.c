#include "../includes/philo.h"

void	*cycle(void *philo)
{
	usleep(10000);
	if (((t_philo *)philo)->index % 2 == 0)
		usleep(10000);
	while (1)
	{
		eating(philo);
		sleeping(philo);
	}
	return (NULL);
}

int init_threads(int nbphilo, t_philo *philos, t_shared *shared)
{
	int i;

	i = -1;
	while (++i < nbphilo)
	{
		philos[i].place = i + 1;
		philos[i].index = i;
		philos[i].last_eat = 0; 
		philos[i].nb_eats = 0;
		philos[i].shared = shared;
		pthread_create(&philos[i].identifier, NULL, cycle, &philos[i]);
		usleep(1);
	}
	return (0);
}

void init_mutexes(t_shared *shared)
{
	int i;

	i = -1;
	while (++i < shared->nb_philo)
		pthread_mutex_init(&shared->forks[i], NULL);
	pthread_mutex_init(&shared->speak, NULL);
}

void destroy_mutexes(t_shared *shared)
{
	int i;

	i = -1;
	while (++i < shared->nb_philo)
		pthread_mutex_destroy(&shared->forks[i]);
	pthread_mutex_destroy(&shared->speak);
}