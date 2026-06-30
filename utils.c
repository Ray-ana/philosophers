/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:11:05 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/06/28 18:44:11 by rzimaeva         ###   ########.fr       */
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
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_atoi(char *str)
{
	int			i;
	int			sign;
	long long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		if (res > 2147483647)
			return (-1);
		i++;
	}
	return (res * sign);
}

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
// convertir secondes (tv.sec) en millisecondes avec une multiplication 
// et microsecondes (tv.usec) en millisecondes avec une division

void	ft_usleep(long long time_in_ms)
{
	long long	start_time;

	start_time = get_current_time();
	while ((get_current_time() - start_time) < time_in_ms)
	{
		usleep(500);
	}
}
