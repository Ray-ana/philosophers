/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 18:23:06 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/06/30 18:07:10 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_struct_globale *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_init(&data->fork_lock[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	return (1);
}

void	destroy_mutex(t_struct_globale *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_destroy(&data->fork_lock[i]);
		pthread_mutex_destroy(&data->philo[i].meal_lock);
		i++;
	}
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->write_lock);
	free(data->philo);
	free(data->fork_lock);
}

int	init_data(t_struct_globale *data, int ac, char **av)
{
	data->nb_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (data->nb_philos <= 0 || data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0)
		return (0);
	if (ac == 6)
	{
		data->max_meals = ft_atoi(av[5]);
		if (data->max_meals <= 0)
			return (0);
	}
	else
		data->max_meals = -1;
	data->end = false;
	return (1);
}

int	alloc_data(t_struct_globale *data)
{
	data->philo = malloc(sizeof(t_philo) * (data->nb_philos));
	data->fork_lock = malloc(sizeof(pthread_mutex_t) * (data->nb_philos));
	if (!data->philo || !data->fork_lock)
	{
		if (data->philo)
			free(data->philo);
		if (data->fork_lock)
			free(data->fork_lock);
		return (0);
	}
	return (1);
}

void	init_forks(t_struct_globale *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		data->philo[i].id = i + 1;
		data->philo[i].s_globale = data;
		data->philo[i].current_meals = 0;
		pthread_mutex_init(&data->philo[i].meal_lock, NULL);
		data->philo[i].left_fork = &data->fork_lock[i];
		if (i == data->nb_philos - 1)
			data->philo[i].right_fork = &data->fork_lock[0];
		else
			data->philo[i].right_fork = &data->fork_lock[i + 1];
		i++;
	}
}
// on doit relier philo a la structure globale pour
// que ca fasse comme une boucle
// fourchette gauche a le meme num que le philo
// alors que celle de droite a celui du voisin