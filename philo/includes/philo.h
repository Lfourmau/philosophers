#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_shared
{
	int				nb_philo;
	int 			time_die;
	int 			time_eat;
	int				time_sleep;
	int				nb_eats;
	long int		time_elapsed;
	pthread_mutex_t	*forks;
	pthread_mutex_t speak;
	struct timeval	start;
}	t_shared;

typedef struct s_philo
{
	pthread_t 		identifier;
	int				place;
	int				last_eat;
	int				nb_eats;
	t_shared 		*shared;
}	t_philo;


int			ft_atoi(const char *str);
int			init_threads(int nbphilo, t_philo *philos, t_shared *shared);
void		init_mutexes(t_shared *shared);
void		destroy_mutexes(t_shared *shared);


#endif
