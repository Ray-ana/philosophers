/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 16:19:09 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/06/30 18:07:16 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_text(char *str, t_philo *philo, int id)
{
	time_t	time;

	time = (get_current_time() - philo->s_globale->start_time);
	pthread_mutex_lock(&philo->s_globale->write_lock);
	if (check_end(philo))
	{
		pthread_mutex_unlock(&philo->s_globale->write_lock);
		return ;
	}
	printf("%ld %d %s\n", time, id, str);
	pthread_mutex_unlock(&philo->s_globale->write_lock);
}

void	*eating(t_philo *philo)
{
	if (check_end(philo))
		return (NULL);
	pthread_mutex_lock(philo->left_fork);
	if (check_end(philo))
		return (pthread_mutex_unlock(philo->left_fork), NULL);
	print_text("has taken a fork", philo, philo->id);
	if (philo->s_globale->nb_philos == 1)
	{
		return (ft_usleep(philo->s_globale->time_to_die),
			pthread_mutex_unlock(philo->left_fork), NULL);
	}
	if (check_end(philo))
		return (pthread_mutex_unlock(philo->left_fork), NULL);
	pthread_mutex_lock(philo->right_fork);
	print_text("has taken a fork", philo, philo->id);
	print_text("is eating", philo, philo->id);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_current_time();
	philo->current_meals++;
	pthread_mutex_unlock(&philo->meal_lock);
	ft_usleep(philo->s_globale->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (NULL);
}

void	sleeping(t_philo *philo)
{
	print_text("is sleeping", philo, philo->id);
	ft_usleep(philo->s_globale->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	print_text("is thinking", philo, philo->id);
}

void	*routine_philos(void *arg)
{
	t_philo	*philo;
	time_t	time_delay;

	philo = (t_philo *)arg;
	time_delay = philo->s_globale->time_to_eat / 2;
	if (philo->id % 2 == 0)
		ft_usleep(time_delay);
	while (1)
	{
		if (check_end(philo))
			return (NULL);
		eating(philo);
		if (check_end(philo))
			return (NULL);
		sleeping(philo);
		thinking(philo);
		ft_usleep(1);
	}
	return (NULL);
}
