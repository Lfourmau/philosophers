#include "../includes/philo.h"

void	*life(void *philo)
{
	//syncro();
	if (((t_philo *)philo)->place % 2 == 0)
		usleep(1000);
	while (1)//changer conndition->Mort ou nb de repas
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
		philos[i].index = i;
		philos[i].place = i + 1;
		shared->is_dead = 0;
		philos[i].nb_eats = 0;
		philos[i].shared = shared;
		gettimeofday(&shared->last_eat[i], NULL);
		pthread_create(&philos[i].identifier, NULL, life, &philos[i]);
	}
	//shared->syncro_stop = 1
	return (0);
}

void init_mutexes(t_shared *shared)
{
	int i;

	i = -1;
	while (++i < shared->nb_philo)
	{
		pthread_mutex_init(&shared->forks[i], NULL);
		pthread_mutex_init(&shared->eat_mutex[i], NULL);
	}
	pthread_mutex_init(&shared->speak, NULL);
}

void destroy_mutexes(t_shared *shared)
{
	int i;

	i = -1;
	while (++i < shared->nb_philo)
	{
		pthread_mutex_destroy(&shared->forks[i]);
		pthread_mutex_destroy(&shared->eat_mutex[i]);
	}
	pthread_mutex_destroy(&shared->speak);
}