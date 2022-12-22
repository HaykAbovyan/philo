/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habovyan <habovyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:23:42 by habovyan          #+#    #+#             */
/*   Updated: 2022/12/22 18:05:23 by habovyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*function(void *temp)
{
	t_philo	*philo;
	t_args	*args;

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
		mutexing_and_printing(philo, "is thinking");
	}
	return (NULL);
}

void	joining_and_mutex_destroying(t_args *args)
{
	int	i;

	i = 0;
	while (++i < args->count)
		pthread_detach((args->philo[i].th));
	i = -1;
	while (++i < args->count)
		pthread_mutex_destroy(&(args->fork[i]));
}

void	is_died(t_args *r, t_philo *p)
{
	int	i;

	while (!(r->if_all_ate_must_eat_time))
	{
		i = 0;
		while (r->must_eat_num != -1 && i < r->count
			&& p[i].count_of_eating >= r->must_eat_num)
			i++;
		if (i == r->count)
			r->if_all_ate_must_eat_time = 1;
		i = -1;
		while (++i < r->count && !(r->smone_died))
		{
			if (r->current_time - p[i].time_of_last_eating > r->time_to_die)
			{
				mutexing_and_printing(p, "died");
				r->smone_died = 1;
			}
		}
		r->current_time = timestamp();
		if (r->smone_died)
			break ;
	}
}

int	start(t_args *args)
{
	int		i;
	t_philo	*philo;

	philo = args->philo;
	i = -1;
	args->time_start = args->current_time;
	while (++i < args->count)
	{
		philo[i].time_of_last_eating = args->current_time;
		if (pthread_create(&philo[i].th, NULL, &function, &philo[i]))
			return (1);
	}
	is_died(args, philo);
	joining_and_mutex_destroying(args);
	return (0);
}
