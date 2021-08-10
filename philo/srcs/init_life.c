/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_life.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourmau <lfourmau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 09:52:49 by lfourmau          #+#    #+#             */
/*   Updated: 2021/08/10 11:16:34 by lfourmau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->shared->syncro == 0)
		usleep(4000);
	if (philo->place % 2 == 1)
		usleep(8000);
	while (1)
	{
		eating(philo);
		sleeping(philo);
	}
	return (NULL);
}

int	init_threads(int nbphilo, t_philo *philos, t_shared *shared)
{
	int	i;

	i = -1;
	shared->syncro = 0;
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
	shared->syncro = 1;
	return (0);
}

void	init_mutexes(t_shared *shared)
{
	int	i;

	i = -1;
	while (++i < shared->nb_philo)
	{
		pthread_mutex_init(&shared->forks[i], NULL);
		pthread_mutex_init(&shared->eat_mutex[i], NULL);
	}
	pthread_mutex_init(&shared->speak, NULL);
}

void	destroy_mutexes(t_shared *shared)
{
	int	i;

	i = -1;
	while (++i < shared->nb_philo)
	{
		pthread_mutex_destroy(&shared->forks[i]);
		pthread_mutex_destroy(&shared->eat_mutex[i]);
	}
	pthread_mutex_destroy(&shared->speak);
}
