/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_with_mutex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 15:46:47 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/06/18 16:05:59 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//initialiser les mutex
int init_mutex(t_struct_globale *info)
{
    int i;

    i = 0;
    while (i < info->nb_philos)
    {
        pthread_mutex_init(&info->fork_lock[i], NULL);
        i++;
    }
    pthread_mutex_init(&info->write_lock, NULL);
    pthread_mutex_init(&info->dead_lock, NULL);
    return (1); //pour pouvoir dire dans le main si tout est bon avec 1 sinon 0
}

void    destroy_mutex(t_struct_globale *info)
{
    int i;

    i = 0;
    while (i < info->nb_philos)
    {
        pthread_mutex_destroy(&info->fork_lock[i]);
        i++;
    }
    free (info->philo);
    free (info->fork_lock);
    free (info);
}

void    wait_mutex(t_struct_globale *info)
{
    int i;
    
    i = 0;
    while (i < info->nb_philos)
    {
        pthread_join(info->philo[i].thread, NULL);
        i++;
    }
}
