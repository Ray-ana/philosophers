/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:11:11 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/07/03 18:11:47 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	join_threads(t_struct_globale *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_join(data->monitor, NULL) != 0)
		return (0);
	return (1);
}

int	launch_threads(t_struct_globale *data)
{
	int	i;

	i = 0;
	data->start_time = get_current_time();
	while (i < data->nb_philos)
	{
		data->philo[i].last_meal_time = data->start_time;
		if (pthread_create(&data->philo[i].thread, NULL, &routine_philos,
				&data->philo[i]) != 0)
			return (0);
		i++;
	}
	if (pthread_create(&data->monitor, NULL, &monitor_routine, data) != 0)
		return (0);
	return (join_threads(data));
}

int	main(int ac, char **av)
{
	t_struct_globale	data;

	if (ac != 5 && ac != 6)
		return (printf("Correct input is: ./philo 2 800 200 200 [2]\n"), 1);
	if (nb_args(ac, av) == 0)
		return (printf("Error: Arguments must be integers\n"), 1);
	if (init_data(&data, ac, av) == 0)
		return (printf("Error: Arguments values must be greater than 0\n"), 1);
	if (alloc_data(&data) == 0 || init_mutex(&data) == 0)
		return (1);
	init_forks(&data);
	if (launch_threads(&data) == 0)
		return (destroy_mutex(&data), 1);
	destroy_mutex(&data);
	return (0);
}
