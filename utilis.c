/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habovyan <habovyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:21:01 by habovyan          #+#    #+#             */
/*   Updated: 2022/12/22 18:07:29 by habovyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	ft_usleep(long long x, t_args *args)
{
	long long	time;

	time = args->current_time;
	while (!(args->smone_died) && !(args->if_all_ate_must_eat_time))
	{
		if (args->current_time - time >= x)
			break ;
	}
}

void	mutexing_and_printing(t_philo *Philo, char *str)
{
	t_args	*args;

	args = Philo->args;
	pthread_mutex_lock(&Philo->args->printf);
	if (*str != 'd' && !(args->if_all_ate_must_eat_time))
	{
		printf("%lld %d %s\n", *Philo->current_time
			- args->time_start, Philo->id + 1, str);
		pthread_mutex_unlock(&Philo->args->printf);
	}
	else
		printf("%lld %d %s\n", *Philo->current_time
			- args->time_start, Philo->id + 1, str);
}
