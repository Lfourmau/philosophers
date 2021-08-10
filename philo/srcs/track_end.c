/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourmau <lfourmau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 09:56:09 by lfourmau          #+#    #+#             */
/*   Updated: 2021/08/10 09:56:41 by lfourmau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	track_death(t_shared *shared, t_philo *philos, int i)
{
	if (get_time(shared->last_eat[i]) > philos->shared->time_die)
	{
		print_messages("is dead", &philos[i], 1);
		pthread_mutex_unlock(&shared->eat_mutex[i]);
		destroy_mutexes(shared);
		return (1);
	}
	return (0);
}

int	track_meals(t_shared *shared, t_philo *philos, int i)
{
	if (philos[i].nb_eats == shared->nb_eats)
		return (1);
	return (0);
}

void	track_end(t_philo *philos, t_shared *shared)
{
	int	i;
	int	j;

	while (1)
	{
		j = 0;
		i = -1;
		while (++i < shared->nb_philo)
		{
			pthread_mutex_lock(&shared->eat_mutex[i]);
			if (track_death(shared, philos, i))
				return ;
			if (shared->nb_eats > 0 && track_meals(shared, philos, i))
				j++;
			pthread_mutex_unlock(&shared->eat_mutex[i]);
			if (j == shared->nb_philo)
			{
				print_messages("bien graille", &philos[i], 1);
				pthread_mutex_unlock(&shared->eat_mutex[i]);
				destroy_mutexes(shared);
				return ;
			}
		}
		usleep(300);
	}
}
