#include "../includes/philo.h"
pthread_mutex_t mutexinit = PTHREAD_MUTEX_INITIALIZER;
int 			shared;

void	*test_thread_fct(void *argp)
{
	int i = 0;
	(void)argp;
	pthread_mutex_lock(&mutexinit);
	printf("Incrementing the bordel...\n");
	while (i < 100000)
	{
		shared++;
		i++;
	}
	pthread_mutex_unlock(&mutexinit);
	return (NULL);
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	pthread_t threads[5];
	int i = 0;
	while (i <= 4)
	{
		pthread_create(&threads[i], NULL, test_thread_fct, NULL);
		i++;
	}
	i = 0;
	while (i <= 4)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	printf("%d\n", shared);
	return (0);
}