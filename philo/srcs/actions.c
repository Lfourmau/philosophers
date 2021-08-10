/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourmau <lfourmau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 09:50:28 by lfourmau          #+#    #+#             */
/*   Updated: 2021/08/10 11:27:03 by lfourmau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	custom_usleep(int reach)
{
	int				time;
	struct timeval	tmp;

	time = 0;
	gettimeofday(&tmp, 0);
	while (time < reach)
	{
		usleep(20);
		time = get_time(tmp);
	}
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->forks[philo->index]);
	print_messages("has taken a fork", philo, 0);
	pthread_mutex_lock(&philo->shared->forks[philo->place \
	% philo->shared->nb_philo]);
	print_messages("has taken a fork", philo, 0);
	print_messages("is eating", philo, 0);
	pthread_mutex_lock(&philo->shared->eat_mutex[philo->index]);
	gettimeofday(&philo->shared->last_eat[philo->index], NULL);
	philo->nb_eats++;
	pthread_mutex_unlock(&philo->shared->eat_mutex[philo->index]);
	custom_usleep(philo->shared->time_eat);
	pthread_mutex_unlock(&philo->shared->forks[philo->index]);
	print_messages("has drop a fork", philo, 0);
	pthread_mutex_unlock(&philo->shared->forks[philo->place % \
	philo->shared->nb_philo]);
	print_messages("has drop a fork", philo, 0);
}

void	sleeping(t_philo *philo)
{
	print_messages("is sleeping", philo, 0);
	custom_usleep(philo->shared->time_sleep);
	print_messages("is thinking", philo, 0);
}
