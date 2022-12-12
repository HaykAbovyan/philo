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
		args->philo[i].count_of_eating = 0;
		args->philo[i].time_of_last_eating = 0;
		args->philo[i].args = args;
	}
}

int mutexes(t_args *args)
{
	int i;

	i = args->count;
	while (--i >= 0)
	{
		if ((pthread_mutex_init(&args->fork[i], NULL)) != 0)
			return (1);
	}
	if ((pthread_mutex_init(&args->eating, NULL)) != 0)
			return (1);
	if ((pthread_mutex_init(&args->printf, NULL)) != 0)
			return (1);
	return (0);
}

int to_pas_args(t_args *args, char **av)
{
	args->count = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	args->if_all_ate_must_eat_time = 0;
	args->smone_died = 0;
	if (args->count < 2 ||args->time_to_die < 0 ||
	args->time_to_eat < 0 || args->time_to_sleep < 0 ||
	args->must_eat_num <= 0)
		return (1);
	if (av[5])
	{
		args->must_eat_num = ft_atoi(av[5]);
		if (args->must_eat_num <= 0)
			return (1);
	}
	else
		args->must_eat_num = -1;
	philosophers(args);
	if (mutexes(args))
		return (1);
	return (0);
}

void eating(philo *Philo)
{
	t_args *args;
	args = Philo->args;
	pthread_mutex_lock(&args->fork[Philo->left_fork]);
	function_to_print();
	pthread_mutex_unlock(&args->fork[Philo->right_fork]);
	funcion_to_print();



}

void *function(void *temp)
{
	philo *Philo;
	Philo = (philo *)temp;
	if (Philo->id % 2)
		usleep(2000);
	while (1)
	{
		eating(Philo);
	}
	
}

void start(t_args *args)
{
	int		i;
	philo	*philo;

	philo = args->philo;
	i = args->count;
	while (--i >= 0)
	{
		if(pthread_create(&philo[i].th, NULL, &function, &philo[i]))
			return (1);
		
	}

}

int main(int ac, char **av)
{
	t_args args;
	int i= 0;
	if (ac == 5 || ac == 6 )
	{
		if (to_pas_args(&args, av))
			return (printf("Error\n"), 0);
		start(&args);
	}
	else
		printf("Error\n");
	return (0);
}