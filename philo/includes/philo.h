#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_struct
{
	int 			shared;
	pthread_mutex_t mutex;
	int res_init;
} t_test;

#endif
