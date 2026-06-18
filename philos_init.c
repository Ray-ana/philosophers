/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 18:23:06 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/06/18 16:05:00 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
        info->philo[i].left_fork = &info->fork_lock[i];
        if (i == info->nb_philos - 1) //le dernier philosophe, la fourchette a sa droite est celle du 0
            info->philo[i].right_fork = &info->fork_lock[0]; //si c'est bien le dernier sa fourchette sera bien 0 (celle du premier) et non 3
        else
            info->philo[i].right_fork = &info->fork_lock[i + 1]; //cas normal
        i++;
    }
}
//fourchette gauche a le meme num que le philo alors que celle de droite a celui du voisin

//le philo lock pour pouvoir mager et unlock pour penser et dormir et laisser les autres manger
void *routine_philos(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg; //le void *arg a ete converti en pointeur de philo avec la struct t_philo rattachee
    while (1)
    {
        if (philo->id % 2 == 0) //etape pour manger si pair philo commence par la fourchette gauche puis droite et vice versa
        {
            pthread_mutex_lock(philo->left_fork);
            pthread_mutex_lock(philo->right_fork);
        }
        else
        {
            pthread_mutex_lock(philo->right_fork);
            pthread_mutex_lock(philo->left_fork);
        }
        usleep (500);
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        usleep (500);
    }
    return (NULL);
}
//pas d'esperluettes car left fork et right fork sont deja des pointeurs alors ont toujours l'update de l'adresse source 