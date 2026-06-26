/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 18:23:06 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/06/26 21:43:59 by rzimaeva         ###   ########.fr       */
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
        pthread_mutex_destroy(&info->philo[i].meal_lock);
        i++;
    }
    free (info->philo);
    free (info->fork_lock);
    free (info);
}

int	init_info(t_struct_globale *info, int ac, char **av)
{
    info->nb_philos = ft_atoi(av[1]);
    info->time_to_die = ft_atoi(av[2]);
    info->time_to_eat = ft_atoi(av[3]);
    info->time_to_sleep = ft_atoi(av[4]);
    if (info->nb_philos <= 0 || info->time_to_die <= 0
        || info->time_to_eat <= 0 || info->time_to_sleep <= 0)
        return (0);
    if (ac == 6)
    {
        info->max_meals = ft_atoi(av[5]);
        if (info->max_meals <= 0)
            return (0);
    }
    else
        info->max_meals = -1; // sinon pas de limite de repas
    return (1);
}

int alloc_info(t_struct_globale *info)
{
    info->philo = malloc(sizeof(t_philo) * (info->nb_philos)); //qund tu sizeof tu mets le type
    info->fork_lock = malloc(sizeof(pthread_mutex_t) * (info->nb_philos)); //nb_philos car il y a le meme nombre de fourchettes que de philos

    if (!info->philo || !info->fork_lock)
    {
        if (info->philo)
            free(info->philo);
        if (info->fork_lock)
            free(info->fork_lock);
        return (0);
    }
    return (1);
}

void init_forks(t_struct_globale *info)
{
    int i;

    i = 0;
    while (i < info->nb_philos)
    {
        info->philo[i].id = i + 1;
        info->philo[i].s_globale = info;
        pthread_mutex_init(&info->philo[i].meal_lock, NULL);
        info->philo[i].left_fork = &info->fork_lock[i];
        if (i == info->nb_philos - 1) //le dernier philosophe, la fourchette a sa droite est celle du 0
            info->philo[i].right_fork = &info->fork_lock[0]; //si c'est bien le dernier sa fourchette sera bien 0 (celle du premier) et non 3
        else
            info->philo[i].right_fork = &info->fork_lock[i + 1]; //cas normal
        i++;
    }
}
//on doit relier philo a la structure globale pour que ca fasse comme une boucle
//fourchette gauche a le meme num que le philo alors que celle de droite a celui du voisin