#include "philo.h"


int timestamp_in_micro()
{
	struct timeval t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000000 + t.tv_usec);
}


int timestamp_in_mili()
{
	struct timeval t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void ft_usleep(int x)
{
	long long int time;

	time = timestamp_in_micro();
	while(1)
	{
		if(timestamp_in_micro() - time >= x)
			break;
	}
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
	if ((pthread_mutex_init(&args->printf, NULL)) != 0)
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
	pthread_mutex_lock(&Philo->args->printf);
	printf("%lld %d %s\n",timestamp_in_mili() - Philo->args->time_start, Philo->id + 1, str);
	pthread_mutex_unlock(&Philo->args->printf);
}

void eating(philo *Philo)
{
	t_args *args;
	args = Philo->args;

	pthread_mutex_lock(&args->fork[Philo->left_fork]);
	mutexing_and_printing(Philo, "has taken a fork");
	pthread_mutex_lock(&args->fork[Philo->right_fork]);
	mutexing_and_printing(Philo, "has taken a fork");
	mutexing_and_printing(Philo, "is eating");
	ft_usleep(args->time_to_eat);
	Philo->time_of_last_eating = timestamp_in_mili() - args->time_start;
	Philo->count_of_eating++;
	pthread_mutex_unlock(&args->fork[Philo->right_fork]);
	pthread_mutex_unlock(&args->fork[Philo->left_fork]);
}

void sleeping(philo *Philo)
{
	mutexing_and_printing(Philo, "is sleeping");
	ft_usleep(Philo->args->time_to_sleep);
}

void *function(void *temp)
{
	philo *Philo;
	Philo = (philo *)temp;
	if (Philo->id % 2)
		usleep(15000);
	while (!(Philo->args->smone_died))
	{
		eating(Philo);
		sleeping(Philo);
		mutexing_and_printing(Philo, "is thinking");
	}
	return (NULL);
}

int mutex_destroy(t_args *args)
{
	int i;
	i = -1;
	while (++i < args->count)
	{
		if (pthread_mutex_destroy(&args->fork[i]))
			return (1);
	}
	if (pthread_mutex_destroy(&args->printf))
		return (1);	
	return (0);
}

int joining(t_args *args, philo *philo)
{
	int i;

	i = -1;
	while (++i < args->count)
	{
		if (pthread_join(philo[i].th, NULL))
			return (1);
	}
	return (0);
}
void is_died(philo *philo)
{
	int i;
	t_args *args;

	args = philo->args;
	printf("here\n");
	i = -1;
	while (1)
	{
		while (++i < args->count)
		{
			if (philo[i].time_of_last_eating >= args->time_to_die)
			{
				mutexing_and_printing(philo, "died");
				return ;
			}
		}
	}
	return ;
}


int start(t_args *args)
{
	int		i;
	philo	*philo;

	philo = args->philo;
	i = -1;
	args->time_start = timestamp_in_mili();
	while (++i < args->count)
	{
		if(pthread_create(&philo[i].th, NULL, &function, &philo[i]))
			return (1);
	}
	is_died(philo);
	if (joining(args, philo))
		return (1);
	if (mutex_destroy(args))
		return (1);
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