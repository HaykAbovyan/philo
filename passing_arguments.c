/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   passing_arguments.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habovyan <habovyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:16:55 by habovyan          #+#    #+#             */
/*   Updated: 2022/12/22 18:01:59 by habovyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philosophers(t_args *args)
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
		args->philo[i].current_time = &args->current_time;
	}
}

int	mutexes(t_args *args)
{
	int	i;

	i = args->count;
	while (--i >= 0)
	{
		if ((pthread_mutex_init(&args->fork[i], NULL)) != 0)
			return (1);
	}
	if ((pthread_mutex_init(&args->printf, NULL)) != 0)
		return (1);
	if ((pthread_mutex_init(&args->meal, NULL)) != 0)
		return (1);
	return (0);
}

int	to_pas_args(t_args *args, char **av)
{
	args->count = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	args->if_all_ate_must_eat_time = 0;
	args->smone_died = 0;
	args->current_time = timestamp();
	if ((args->count < 0 && args->count >= 200) || args->time_to_die < 0
		|| args->time_to_eat < 0 || args->time_to_sleep < 0)
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
