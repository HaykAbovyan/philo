#include "philo.h"


long long diff(long long past, long long now)
{
	return (past - now);
}

int timestamp()
{
	struct timeval t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void ft_usleep(long long x, t_args *args)
{
	long long time;

	time = timestamp();
	while(!(args->smone_died))
	// while(1)
	{
		if(diff(timestamp(), time) >= x)
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
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
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
	t_args *args;
	args = Philo->args;
	pthread_mutex_lock(&Philo->args->printf);
	if (!(args->smone_died))
		printf("%lld %d %s\n",timestamp() - args->time_start, Philo->id + 1, str);
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
	//
	pthread_mutex_lock(&args->meal);
	mutexing_and_printing(Philo, "is eating");
	Philo->time_of_last_eating = timestamp();
	pthread_mutex_unlock(&args->meal);
	//
	ft_usleep(args->time_to_eat, args);
	Philo->count_of_eating++;
	pthread_mutex_unlock(&args->fork[Philo->right_fork]);
	pthread_mutex_unlock(&args->fork[Philo->left_fork]);
}

void sleeping(philo *Philo)
{
	t_args *args;
	args = Philo->args;
	mutexing_and_printing(Philo, "is sleeping");
	ft_usleep(Philo->args->time_to_sleep, args);
}

void *function(void *temp)
{
	philo *Philo;
	t_args *args;
	Philo = (philo *)temp;
	args = Philo->args;
	if (Philo->id % 2)
		usleep(15000);
	while (!(args->smone_died))
	{
		eating(Philo);
		if (args->if_all_ate_must_eat_time)
			break ;
		sleeping(Philo);
		mutexing_and_printing(Philo, "is thinking");
	}
	return (NULL);
}


void joining_and_mutex_destroying(t_args *args, philo *philo)
{
	int i;

	i = -1;
	while (++i < args->count)
		pthread_join(philo[i].th, NULL);
	i = -1;
	while (++i < args->count)
		pthread_mutex_destroy(&(args->fork[i]));
	pthread_mutex_destroy(&(args->printf));
	pthread_mutex_destroy(&(args->meal));

}


void	is_died(t_args *r, philo *p)
{
	int i;
	
	while (!(r->if_all_ate_must_eat_time) )
	{
		i = -1;
		while (++i < r->count && !(r->smone_died))
		{
			if (diff(timestamp(), p[i].time_of_last_eating) > r->time_to_die)
			{		
				mutexing_and_printing(p, "died");
				r->smone_died = 1;
			}			
		}
		if (r->smone_died)
			break ;
		i = 0;
		while (r->must_eat_num != -1 && i < r->count && p[i].count_of_eating >= r->must_eat_num)
			i++;
		if (i == r->count)
			r->if_all_ate_must_eat_time = 1;
	}
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
		philo[i].time_of_last_eating = timestamp();
	}
	is_died(args, philo);
	joining_and_mutex_destroying(args, philo);
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