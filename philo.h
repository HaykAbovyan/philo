#ifndef PHILO_H
#define PHILO_H

#include <stdlib.h>
#include <pthread.h>

typedef struct philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	pthread_t		th;
}				philo;

typedef struct t_args{
	int				count;
	int				time_to_die; // miliseconds
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_num;
	philo			philo[200];
	pthread_mutex_t fork[200];
}				t_args;


#endif 