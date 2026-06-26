/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 15:46:06 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/06/26 21:05:57 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_struct_globale	*info;
	int					done_eating;

	info = (t_struct_globale *)arg;
	while (1)
	{
		done_eating = 0;
		if (check_on_philos(info, &done_eating) == 1) //parce qu'on a mis return 1
			return (NULL);
		pthread_mutex_lock(&info->dead_lock);
		if (info->max_meals != -1 && done_eating == info->nb_philos)
		{
			info->end = true;
			pthread_mutex_unlock(&info->dead_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&info->dead_lock);
		ft_usleep(1);
	}
	return (NULL);
}
//pour info->max_meals != -1, le minimum c'est 0 car il est initie a 0 et si y'a -1 c'est que y'a rien

int	check_on_philos(t_struct_globale *info, int *done_eating)
{
	int	i;

	i = 0;
	while (i < info->nb_philos) //pour verifier les morts
	{
        pthread_mutex_lock(&info->philo[i].meal_lock);
		pthread_mutex_lock(&info->dead_lock);
        if ((get_current_time() - info->philo[i].last_meal_time) > info->time_to_die)
        {
            info->end = true;
            pthread_mutex_lock(&info->write_lock);
            printf("%lld %d died\n", get_current_time(), info->philo[i].id);
            pthread_mutex_unlock(&info->write_lock);
            pthread_mutex_unlock(&info->philo[i].meal_lock);
            pthread_mutex_unlock(&info->dead_lock);
			return (1);
        }
		pthread_mutex_unlock(&info->dead_lock);
		if (info->max_meals != -1 && (info->philo[i].nb_meals >= info->max_meals))
			(*done_eating)++;
		pthread_mutex_unlock(&info->philo[i].meal_lock);
		i++;
	}
	return (0);
}
// pour (*done_eating)++ on modifie l'adresse entiere vu que c'est un * et pas une simple variable attention
