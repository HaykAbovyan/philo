/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habovyan <habovyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:15:33 by habovyan          #+#    #+#             */
/*   Updated: 2022/12/22 18:03:09 by habovyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *Philo)
{
	t_args	*args;

	args = Philo->args;
	pthread_mutex_lock(&args->fork[Philo->left_fork]);
	mutexing_and_printing(Philo, "has taken a fork");
	pthread_mutex_lock(&args->fork[Philo->right_fork]);
	mutexing_and_printing(Philo, "has taken a fork");
	mutexing_and_printing(Philo, "is eating");
	Philo->time_of_last_eating = *Philo->current_time;
	ft_usleep(args->time_to_eat, args);
	Philo->count_of_eating++;
	pthread_mutex_unlock(&args->fork[Philo->right_fork]);
	pthread_mutex_unlock(&args->fork[Philo->left_fork]);
}

void	sleeping(t_philo *Philo)
{
	t_args	*args;

	args = Philo->args;
	mutexing_and_printing(Philo, "is sleeping");
	ft_usleep(Philo->args->time_to_sleep, args);
}
