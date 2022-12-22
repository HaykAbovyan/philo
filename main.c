/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habovyan <habovyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:15:24 by habovyan          #+#    #+#             */
/*   Updated: 2022/12/22 17:39:20 by habovyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_not_num(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		j = -1;
		if (av[i][0] == '0')
			return (1);
		while (av[i][++j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
		}
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_args	args;

	if (ac == 5 || ac == 6)
	{
		if (is_not_num(ac, av))
			return (printf("error\n"), 0);
		if (to_pas_args(&args, av))
			return (printf("error\n"), 0);
		if (start(&args))
			return (printf("error\n"), 0);
	}
	else
		printf("Error3\n");
	return (0);
}
