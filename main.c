/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:11:11 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/06/26 21:46:27 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int    join_threads(t_struct_globale *info)
{
    int i;
    
    i = 0;
    while (i < info->nb_philos)
    {
        if (pthread_join(info->philo[i].thread, NULL) != 0)
            return (0);
        i++;
    }
    if (pthread_join(info->monitor, NULL) != 0)
            return (0);
    return (1);
}
//permet de lancer les threads apres avoir boucler sur chaque philo
int    launch_threads(t_struct_globale *info)
{
    int i;

    i = 0;
    info->start_time = get_current_time();
    while (i < info->nb_philos)
    {
        info->philo[i].last_meal_time = info->start_time; //impose de commencer ici
        if (pthread_create(&info->philo[i].thread, NULL, \
            &routine_philos, &info->philo[i]) != 0) //on met en if au cas ou elle echoue comme ca on peut l'arreter direct
            return (0);
        i++;
    }
    if (pthread_create(&info->monitor, NULL, &monitor_routine, info) != 0)
        return (0);
    return (join_threads(info));
}

int main(int ac, char **av)
{
    t_struct_globale info;

    if (ac != 5 && ac != 6)
        error_exit("Wrong input:\nCorrect input is: ./philo 1 800 200 200 [1]");
    if (nb_args(ac, av) == 0)
        return (printf("Error: Arguments must be integers\n"), 1);
    if (init_info(&info, ac, av) == 0)
        return (printf("Error: Arguments values must be greater than 0\n"), 1);
    if (alloc_info(&info) == 0 || init_mutex(&info) == 0)
        return (1);
    init_forks(&info);
    if (launch_threads(&info) == 0)
        return (destroy_mutex(&info), 1);
    destroy_mutex(&info);
    return (0);
}
