#include "../includes/philo.h"

void	*cycle(void *param)
{
	printf("THREAD NUMBER --> %d\n", ((t_philo *)param)->place);
	return (NULL);
}

int init_threads(int nbphilo, t_philo *philos, t_shared *shared)
{
	int i;

	i = -1;
	while (++i < nbphilo)
	{
		philos[i].place = i + 1;
		philos[i].last_eat = 0; 
		philos[i].nb_eats = 0;
		philos[i].shared = shared;
		pthread_create(&philos[i].identifier, NULL, cycle, &philos[i]);
		usleep(2);
		//pthread_join(philos[i].identifier, NULL);
	}
	return (0);
}

void init_mutex(t_shared *shared)
{
	int i;

	i = -1;
	while (++i < shared->nb_philo)
		pthread_mutex_init(&shared->forks[i], NULL);
}

void destroy_mutex(t_shared *shared)
{
	int i;

	i = -1;
	while (++i < shared->nb_philo)
		pthread_mutex_destroy(&shared->forks[i]);
}