#ifndef PHILO_H
#define PHILO_H

#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>


struct s_args;

typedef struct philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				count_of_eating;
	long long int 	time_of_last_eating;
	pthread_t		th;
	struct s_args	*args;
}				philo;

typedef struct s_args
{
	int				count;
	int				time_to_die; // miliseconds
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_num;
	int				if_all_ate_must_eat_time;
	int				smone_died;
	philo			philo[200];
	pthread_mutex_t fork[200];
	pthread_mutex_t eating;
	pthread_mutex_t printf;
}				t_args;

int	ft_atoi(const char *str);

#endif 