/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:11:08 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/06/18 14:00:52 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	nb_args(int ac, char **av)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (ac < 5 || ac > 6)
		return (0);
	i = 1;
	while (i < ac) // il verifie si chaque arg est bon
	{
		j = 0;
		while (av[i][j]) // si cest pas une numero on arrete
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	init_info(t_struct_globale *info, int ac, char **av)
{
	info->nb_philos = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (info->nb_philos <= 0 || info->time_to_die <= 0
        || info->time_to_eat <= 0 || info->time_to_sleep <= 0)
		return (0);
	if (ac == 6)
	{
        info->max_meals = ft_atoi(av[5]);
		if (info->max_meals <= 0)
			return (0);
	}
	else
		info->max_meals = -1; // sinon pas de limite de repas
	return (1);
}