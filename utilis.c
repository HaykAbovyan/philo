/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habovyan <habovyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:21:01 by habovyan          #+#    #+#             */
/*   Updated: 2022/12/24 15:31:21 by habovyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

int	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	ft_usleep(long long x, t_args *args)
{
	long long	time;

	time = timestamp();
	while (!(args->smone_died) && !(args->if_all_ate_must_eat_time))
	{
		if (time_diff(time, timestamp()) >= x)
			break ;
		usleep(50);
	}
}

void	mutexing_and_printing(t_args *args, int id, char *str)
{
	pthread_mutex_lock(&args->printf);
	if (!(args->smone_died))
	{
		printf("%lli ", timestamp() - args->time_start);
		printf("%i ", id + 1);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&args->printf);
	return ;
}
