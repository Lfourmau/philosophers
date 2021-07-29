#include "../includes/philo.h"

int parsing(int argc, char **argv, t_shared *shared)
{
	if (argc != 5 && argc != 6)
		return (1);
	shared->nb_philo = ft_atoi(argv[1]);
	shared->time_die = ft_atoi(argv[2]);
	shared->time_eat = ft_atoi(argv[3]);
	shared->time_sleep = ft_atoi(argv[4]);
	if (shared->nb_philo <= 0 || shared->time_die <= 0
	|| shared->time_eat <= 0 || shared->time_sleep <= 0)
		return (1);
	if (argc == 6)
		shared->nb_eats = ft_atoi(argv[5]);
	else
		shared->nb_eats = 0;
	return (0);
}

int main(int argc, char **argv)
{
	t_philo *philos;
	t_shared shared;

	gettimeofday(&shared.start, NULL);
	if (parsing(argc, argv, &shared))
		return (1);
	shared.forks = malloc(sizeof(pthread_mutex_t) * shared.nb_philo);
	shared.last_eat = malloc(sizeof(struct timeval) * shared.nb_philo);
	philos = malloc(sizeof(t_philo) * shared.nb_philo);
	init_mutexes(&shared);
	init_threads(shared.nb_philo, philos, &shared);
	track_end(philos, &shared);
	destroy_mutexes(&shared);
	return (0);
}