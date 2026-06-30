/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 15:46:06 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/06/30 18:07:48 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_struct_globale	*data;
	int					done_eating;

	data = (t_struct_globale *)arg;
	while (1)
	{
		done_eating = 0;
		if (check_on_philos(data, &done_eating) == 1)
		{
			pthread_mutex_lock(&data->dead_lock);
			data->end = true;
			pthread_mutex_unlock(&data->dead_lock);
			return (NULL);
		}
		if (data->max_meals != -1 && done_eating == data->nb_philos)
		{
			pthread_mutex_lock(&data->dead_lock);
			data->end = true;
			pthread_mutex_unlock(&data->dead_lock);
			return (NULL);
		}
		ft_usleep(1);
	}
	return (NULL);
}

int	check_on_philos(t_struct_globale *data, int *must_eat)
{
	int	i;

	i = 0;
	*must_eat = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&data->philo[i].meal_lock);
		if (data->max_meals != -1)
		{
			if (data->philo[i].current_meals >= data->max_meals)
				(*must_eat)++;
		}
		if ((get_current_time()
				- data->philo[i].last_meal_time) > data->time_to_die)
		{
			print_text("died", &data->philo[i], data->philo[i].id);
			pthread_mutex_unlock(&data->philo[i].meal_lock);
			return (1);
		}
		pthread_mutex_unlock(&data->philo[i].meal_lock);
		i++;
	}
	return (0);
}
//-1 c'est infini donc si c'est pas infini t'as mis un max_meal