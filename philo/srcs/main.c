/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourmau <lfourmau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 09:54:01 by lfourmau          #+#    #+#             */
/*   Updated: 2021/08/10 11:05:07 by lfourmau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_arguments(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
				return (1);
			j++;
		}
		if (ft_atoi(argv[i]) > 2147483647 || ft_atoi(argv[i]) < -2147483648)
			return (1);
		i++;
	}
	return (0);
}

int	parsing(int argc, char **argv, t_shared *shared)
{
	if (argc != 5 && argc != 6)
		return (1);
	if (check_arguments(argv))
		return (1);
	if (argc == 6)
		shared->nb_eats = ft_atoi(argv[5]);
	else
		shared->nb_eats = 0;
	shared->nb_philo = ft_atoi(argv[1]);
	shared->time_die = ft_atoi(argv[2]);
	shared->time_eat = ft_atoi(argv[3]);
	shared->time_sleep = ft_atoi(argv[4]);
	if (shared->nb_philo <= 0 || shared->time_die < 0
		|| shared->time_eat < 0
		|| shared->time_sleep <= 0 || shared->nb_eats < 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo		*philos;
	t_shared	shared;

	if (parsing(argc, argv, &shared))
		return (1);
	shared.forks = malloc(sizeof(pthread_mutex_t) * shared.nb_philo);
	shared.eat_mutex = malloc(sizeof(pthread_mutex_t) * shared.nb_philo);
	shared.last_eat = malloc(sizeof(struct timeval) * shared.nb_philo);
	philos = malloc(sizeof(t_philo) * shared.nb_philo);
	init_mutexes(&shared);
	gettimeofday(&shared.start, NULL);
	init_threads(shared.nb_philo, philos, &shared);
	track_end(philos, &shared);
	free(shared.forks);
	free(shared.eat_mutex);
	free(shared.last_eat);
	free(philos);
	return (0);
}
