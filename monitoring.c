/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 15:46:06 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/06/18 16:24:17 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//permet de lancer les threads apres avoir boucler sur chaque philo
void    launch_threads(t_struct_globale *info)
{
    int i;

    i = 0;
    while (i < info->nb_philos)
    {
        pthread_create(&info->philo[i].thread, NULL, &routine_philos, &info->philo[i]);
        i++;
    }
}

void	*monitor_routine(void *arg)
{
	t_struct_globale	*info;
	int					i;

	info = (t_struct_globale *)arg;
	while (1)
	{
		i = 0;
		while (i < info->nb_philos)
		{
			pthread_mutex_lock(&info->dead_lock);
            if (get_current_time() - info->philo[i].last_meal_time > info->time_to_die)
            {
                info->end = true; //la simulation s'arrête
                printf("The philo %d is dead...;(\n", info->philo[i].id);
                pthread_mutex_unlock(&info->dead_lock);
                return (NULL);
            }
            pthread_mutex_unlock(&info->dead_lock);
            i++;
		}
		usleep(1000);
	}
	return (NULL);
}