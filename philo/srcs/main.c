#include "../includes/philo.h"

void	*increment(void *ptr)
{
	int i = 0;
	pthread_mutex_lock(&((t_test *)ptr)->mutex);
	printf("Increm lauched...\n");
	while (i < 200000)
	{
		((t_test *)ptr)->shared++;
		i++;
	}
	pthread_mutex_unlock(&((t_test *)ptr)->mutex);
	printf("Increm finished...\n");
	return (NULL);
}

int main()
{
	t_test *mutex = malloc(sizeof(t_test *));
	mutex->shared = 0;
	mutex->res_init = pthread_mutex_init(&mutex->mutex, NULL);
	pthread_t threads[5];

	int i = 0;
	while (i <= 4)
	{
		pthread_create(&threads[i], NULL, increment, (void *)mutex);
		i++;
	}
	i = 0;
	while (i <= 4)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	printf("%d\n", mutex->shared);
	return (0);
}