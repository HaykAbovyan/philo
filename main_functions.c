/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habovyan <habovyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:23:42 by habovyan          #+#    #+#             */
/*   Updated: 2022/12/24 15:28:01 by habovyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*function(void *temp)
{
	int		i;
	t_philo	*philo;
	t_args	*args;

	i = 0;
	philo = (t_philo *)temp;
	args = philo->args;
	if (philo->id % 2)
		usleep(15000);
	while (!(args->smone_died))
	{
		eating(philo);
		if (args->if_all_ate_must_eat_time)
			break ;
		sleeping(philo);
		mutexing_and_printing(args, philo->id, "is thinking");
		i++;
	}
	return (NULL);
}

void	joining_and_mutex_destroying(t_args *args)
{
	int	i;

	i = 0;
	while (++i < args->count)
		pthread_join(args->philo[i].th, NULL);
	i = -1;
	while (++i < args->count)
		pthread_mutex_destroy(&(args->fork[i]));
	pthread_mutex_destroy(&args->printf);
}

void	is_died(t_args *r, t_philo *p)
{
	int	i;

	while (!(r->if_all_ate_must_eat_time))
	{
		i = -1;
		while (++i < r->count && !(r->smone_died))
		{
			pthread_mutex_lock(&r->meal);
			if (time_diff(p[i].t_last_meal, timestamp()) > r->time_to_die)
			{
				mutexing_and_printing(r, p->id, "died");
				r->smone_died = 1;
			}
			pthread_mutex_unlock(&r->meal);
			usleep(100);
		}
		if (r->smone_died)
			break ;
		i = 0;
		while (r->must_eat_num != -1 && i < r->count
			&& p[i].count_of_eating >= r->must_eat_num)
			i++;
		if (i == r->count)
			r->if_all_ate_must_eat_time = 1;
	}
}

int	start(t_args *args)
{
	int		i;
	t_philo	*philo;

	philo = args->philo;
	i = 0;
	args->time_start = timestamp();
	while (i < args->count)
	{
		if (pthread_create(&philo[i].th, NULL, &function, &philo[i]))
			return (1);
		philo[i].t_last_meal = timestamp();
		i++;
	}
	is_died(args, philo);
	joining_and_mutex_destroying(args);
	return (0);
}
