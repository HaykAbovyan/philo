/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habovyan <habovyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:15:33 by habovyan          #+#    #+#             */
/*   Updated: 2022/12/24 15:26:38 by habovyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *Philo)
{
	t_args	*args;

	args = Philo->args;
	pthread_mutex_lock(&args->fork[Philo->left_fork]);
	mutexing_and_printing(args, Philo->id, "has taken a fork");
	pthread_mutex_lock(&args->fork[Philo->right_fork]);
	mutexing_and_printing(args, Philo->id, "has taken a fork");
	pthread_mutex_lock(&args->meal);
	mutexing_and_printing(args, Philo->id, "is eating");
	Philo->t_last_meal = timestamp();
	pthread_mutex_unlock(&args->meal);
	ft_usleep(args->time_to_eat, args);
	Philo->count_of_eating++;
	pthread_mutex_unlock(&args->fork[Philo->right_fork]);
	pthread_mutex_unlock(&args->fork[Philo->left_fork]);
}

void	sleeping(t_philo *Philo)
{
	t_args	*args;

	args = Philo->args;
	mutexing_and_printing(args, Philo->id, "is sleeping");
	ft_usleep(Philo->args->time_to_sleep, args);
}
