/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_deux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 21:15:58 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/06/26 21:26:18 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_end(t_philo *philo)
{
	pthread_mutex_lock(&philo->s_globale->dead_lock);
	if (philo->s_globale->end == true)
	{
		pthread_mutex_unlock(&philo->s_globale->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->s_globale->dead_lock);
	return (0);
}

long long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
//convertir secondes (tv.sec) en millisecondes avec une multiplication et microsecondes (tv.usec) en millisecondes avec une division

void    ft_usleep(long long time_in_ms)
{
    long long   start_time;

    start_time = get_current_time();
    while ((get_current_time() - start_time) < time_in_ms)
    {
        usleep(500); // S'endort par petites tranches de 500 microsecondes
    }
}

