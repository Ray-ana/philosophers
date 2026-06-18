/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 18:23:06 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/06/18 14:00:52 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//initialiser les mutex
int init_mutexes(t_struct_globale *info)
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

void init_philos(t_struct_globale *info)
{
    int i;

    i = 0;
    while (i < info->nb_philos)
    {
        info->philos[i].id = i + 1;
        info->philos[i].left_fork = &info->fork_lock[i];
        if (i == info->nb_philos - 1) //le dernier philosophe, la fourchette a sa droite est celle du 0
            info->philos[i].right_fork = &info->fork_lock[0]; //si c'est bien le dernier sa fourchette sera bien 0 (celle du premier) et non 3
        else
            info->philos[i].right_fork = &info->fork_lock[i + 1]; //cas normal
        i++;
    }
}

//fourchette gauche a le meme num que le philo alors que celle de droite a celui du voisin


//permet de lancer les threads apres avoir boucler sur chaque philo
void    launch_threads(t_struct_globale *info)
{
    int i;

    i = 0;
    while (i < info->nb_philos)
    {
        pthread_create(info->philos[i], NULL, &routine, );
        i++;
    }
}

void *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg; //le void *arg a ete converti en pointeur de philo avec la struct t_philo rattachee
    while (1)
    {
        pthread_mutex_lock(&philo->fourchette_gauche);
        pthread_mutex_lock(philo->fourchette_droite);
        pthread_mutex_unlock(&philo->fourchette_gauche);
        pthread_mutex_unlock(philo->fourchette_droite);
    }
    return (NULL);
}