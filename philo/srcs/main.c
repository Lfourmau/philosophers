#include "../includes/philo.h"

void	*increment(void *ptr)
{
	int i = 0;
	pthread_mutex_lock(&((t_test *)ptr)->mutex);
	printf("Increm lauched...\n");
	while (i < 100000)
	{
		((t_test *)ptr)->shared++;
		i++;
	}
	pthread_mutex_unlock(&((t_test *)ptr)->mutex);
	return (NULL);
}

int main()
{
	t_test *mutex = malloc(sizeof(t_test *));
	mutex->shared = 0;
	mutex->res_init = pthread_mutex_init(&mutex->mutex, NULL);
	pthread_t threads[10];
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	printf("%ld\n%d\n", current_time.tv_sec, current_time.tv_usec);

	int i = 0;
	while (i <= 9)
	{
		pthread_create(&threads[i], NULL, increment, (void *)mutex);
		i++;
	}
	i = 0;
	while (i <= 9)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	printf("%d\n", mutex->shared);
	return (0);
}