#include "../includes/philo.h"

void	print_messages(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->speak);
	printf("%d Philo %d %s\n", get_time(philo->shared->start), philo->place, str);
	if (philo->shared->is_dead == 0)
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
	int i = -1;

	gettimeofday(&shared.start, NULL);
	if (parsing(argc, argv, &shared))
		return (1);
	shared.forks = malloc(sizeof(pthread_mutex_t) * shared.nb_philo);
	shared.last_eat = malloc(sizeof(int) * shared.nb_philo);
	philos = malloc(sizeof(t_philo) * shared.nb_philo);
	init_mutexes(&shared);
	init_threads(shared.nb_philo, philos, &shared);
	while (1)
	{
		//i = -1;
		//while (++i < shared.nb_philo)
		//	if (philos[i].nb_eats < philos->shared->nb_eats)
		//		break;
		//if (i == shared.nb_philo)
		//{
		//	shared.is_dead = 1;
		//	print_messages("Everybody is bien mangé", &philos[i]);
		//	exit(1);
		//}
		i = -1;
		while (++i < shared.nb_philo)
			if (check_end(&philos[i]) == 1)
				exit(1);
	}
	i = -1;
	while (++i < shared.nb_philo)
		pthread_join(philos[i].identifier, NULL);
	destroy_mutexes(&shared);
	return (0);
}