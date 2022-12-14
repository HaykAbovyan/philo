#include "philo.h"


int timestamp()
{
	struct timeval t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

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
	if ((pthread_mutex_init(&args->usleep, NULL)) != 0)
			return (1);
	return (0);
}

int to_pas_args(t_args *args, char **av)
{
	args->count = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]) * 1000;
	args->time_to_eat = ft_atoi(av[3]) * 1000;
	args->time_to_sleep = ft_atoi(av[4]) * 1000;
	args->if_all_ate_must_eat_time = 0;
	args->smone_died = 0;
	if (args->count < 2 ||args->time_to_die < 0 ||
	args->time_to_eat < 0 || args->time_to_sleep < 0)
		return (printf("Error1"), 1);
	if (av[5])
	{
		args->must_eat_num = ft_atoi(av[5]);
		if (args->must_eat_num <= 0)
			return (printf("Error2"), 1);
	}
	else
		args->must_eat_num = -1;
	philosophers(args); 
	if (mutexes(args))
		return (printf("Error3"), 1);
	return (0);
}

void mutexing_and_printing(philo *Philo, char *str)
{
	int tmp;

	tmp = 0;
	if (str[0] == 'l')
		tmp = Philo->left_fork;
	else if (str[0] == 'r')
		tmp = Philo->right_fork;
	pthread_mutex_lock(&Philo->args->printf);
	printf("%d has taken a %s, which id is %d\n", Philo->id + 1, str, tmp + 1);
	pthread_mutex_unlock(&Philo->args->printf);
}

void eating(philo *Philo)
{
	t_args *args;
	args = Philo->args;
	//eating
	pthread_mutex_lock(&args->fork[Philo->left_fork]);
	mutexing_and_printing(Philo, "left fork");
	pthread_mutex_lock(&args->fork[Philo->right_fork]);
	mutexing_and_printing(Philo, "right fork");
	pthread_mutex_lock(&Philo->args->printf);
	printf("%lld %d is eating\n", timestamp() - Philo->args->time_start, Philo->id + 1);
	pthread_mutex_unlock(&Philo->args->printf);
	//pthread_mutex_lock(&Philo->args->usleep);
	//usleep(Philo->args->time_to_eat);
	//pthread_mutex_unlock(&Philo->args->usleep);
	Philo->count_of_eating++;
	pthread_mutex_unlock(&args->fork[Philo->right_fork]);
	pthread_mutex_unlock(&args->fork[Philo->left_fork]);
	//end of eating
}

void *function(void *temp)
{
	philo *Philo;
	Philo = (philo *)temp;
	if (Philo->id % 2)
		usleep(15000);
	// while (1)
	// {
		eating(Philo);
	// }
	// pthread_mutex_lock(&Philo->args->eating);
	// printf("my id is %d and my left fork is %d amd left fork is %d", Philo->id, Philo->left_fork, Philo->right_fork);
	// pthread_mutex_unlock(&Philo->args->eating);
	
}

int start(t_args *args)
{
	int		i;
	philo	*philo;

	philo = args->philo;
	i = -1;
	args->time_start = timestamp();
	while (++i < args->count)
	{
		if(pthread_create(&philo[i].th, NULL, &function, &philo[i]))
			return (1);
	}
	i = -1;
	while (++i < args->count)
	{
		if (pthread_join(philo[i].th, NULL))
			return (1);
	}
	return (0);
}

int main(int ac, char **av)
{
	t_args args;
	int i= 0;
	if (ac == 5 || ac == 6 )
	{
		if (to_pas_args(&args, av))
			return (printf("Error1\n"), 0);
		if (start(&args))
			return (printf("Error2\n"), 0);
	}
	else
		printf("Error3\n");
	return (0);
}