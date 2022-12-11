#include "philo.h"


void philosophers(t_args *args)
{
	int	i;
	i = args->count;
	while (--i >= 0)
	{
		args->philo[i].id = i;
		args->philo[i].left_fork = i;
		args->philo[i].right_fork = (i + 1) % args->count;
	}
}

void mutexes(t_args *args)
{
	int i;

	i = args->count;
	while (--i >= 0)
		pthread_mutex_init(&args->fork[i], NULL);
	
}

int to_pass_args(t_args *args, char **av)
{
	args->count = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		args->must_eat_num = ft_atoi(av[5]);
	else
		args->must_eat_num = 0;
	if (args->count < 2 ||args->time_to_die < 0 ||
	args->time_to_eat < 0 || args->time_to_sleep < 0)
		return (1);
	philosophers(args);
	mutexes(args);
	return (0);
}

void *func(void *a)
{
	t_args *args;
	args = (void *)a;
	if (args->philo->id  % 2 == 0)
		usleep(2);
	eating(args);
	sleeping(args);
	thinking(args); 
}

void start(t_args *args)
{
	int i;
	i = args->count;
	while (--i >= 0)
		pthread_create(args->philo[i].th, NULL, func, args);
	i = args->count;

	
}

int main(int ac, char **av)
{
	t_args *args;

	if (ac == 5 || ac == 6 )
	{
		if (to_pas_args(args, av))
		{
			printf("Error\n");
			return (0);
		}
		start(args);
	}
	printf("Error\n");
	return (0);
}