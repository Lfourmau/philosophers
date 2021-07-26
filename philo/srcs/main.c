#include "../includes/philo.h"

void	*test_thread_fct(void *input)
{
	int i = 0;
	pthread_mutex_lock(&((t_test *)input)->mutex);
	printf("Incrementing the bordel...\n");
	while (i < 200000)
	{
		((t_test *)input)->shared++;
		i++;
	}
	pthread_mutex_unlock(&((t_test *)input)->mutex);
	return (NULL);
}

int main(int argc, char **argv)
{
	t_test *mutex_test = (t_test *)malloc(sizeof(t_test));
	mutex_test->res_init = pthread_mutex_init(&mutex_test->mutex, NULL);
	mutex_test->shared = 0;
	(void)argc;
	(void)argv;
	pthread_t threads[5];
	int i = 0;
	while (i <= 4)
	{
		pthread_create(&threads[i], NULL, test_thread_fct, (void *)mutex_test);
		i++;
	}
	i = 0;
	while (i <= 4)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	printf("%d\n", mutex_test->shared);
	return (0);
}