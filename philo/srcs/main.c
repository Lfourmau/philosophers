#include "../includes/philo.h"

void	print_messages(char *str, t_philo *philo)
{
	//pthread_mutex_lock(&philo->shared->speak);
	//printf("%lu Philo %d %s\n", gettime(), philo->place, str);
	//pthread_mutex_unlock(&philo->shared->speak);
}

int	get_time(struct timeval time_one)
{
	struct timeval time_two;
	long int first_time;
	long int second_time;

	gettimeofday(&time_two, NULL);
	first_time = time_one.tv_sec * 1000 + time_one.tv_usec /1000;
	second_time = time_two.tv_sec * 1000 + time_two.tv_usec /1000;
	return (second_time - first_time);
}

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

	if (parsing(argc, argv, &shared))
		return (1);
	shared.forks = malloc(sizeof(pthread_mutex_t) * shared.nb_philo);
	philos = malloc(sizeof(t_philo) * shared.nb_philo);
	init_mutexes(&shared);
	init_threads(shared.nb_philo, philos, &shared);
	destroy_mutexes(&shared);
	return (0);
}