/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habovyan <habovyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:18:19 by habovyan          #+#    #+#             */
/*   Updated: 2022/12/24 11:47:14 by habovyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include<stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

struct	s_args;

typedef struct philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				count_of_eating;
	long long int	time_of_last_eating;
	long long		*current_time;
	pthread_t		th;
	struct s_args	*args;
	int				test;
}				t_philo;

typedef struct s_args
{
	int				count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_num;
	int				if_all_ate_must_eat_time;
	int				smone_died;
	long long		current_time;
	long long		time_start;
	t_philo			philo[200];
	pthread_mutex_t	fork[200];
	pthread_mutex_t	printf;
}				t_args;

int		ft_atoi(const char *str);
int		to_pas_args(t_args *args, char **av);
int		start(t_args *args);
void	eating(t_philo *Philo);
void	sleeping(t_philo *Philo);
int		timestamp(void);
void	ft_usleep(long long x, t_args *args);
void	mutexing_and_printing(t_philo *Philo, char *str);

#endif 