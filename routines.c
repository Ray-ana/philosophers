/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 16:19:09 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/06/26 21:16:18 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *routine_eating(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg; //le void *arg a ete converti en pointeur de philo avec la struct t_philo rattachee
    if (philo->id % 2 == 0) //etape pour manger si pair philo commence par la fourchette gauche puis droite et vice versa
        routine_eating_details(philo, philo->left_fork, philo->right_fork);
    else
        routine_eating_details(philo, philo->right_fork, philo->left_fork);
    return (NULL);        
}

void    *routine_eating_details(t_philo *philo, pthread_mutex_t *first_fork, pthread_mutex_t *second_fork)
{
    pthread_mutex_lock(first_fork);
    pthread_mutex_lock(&philo->s_globale->write_lock);
    printf("%lld %d has taken a fork\n", get_current_time(), philo->id);
    pthread_mutex_unlock(&philo->s_globale->write_lock);
    //if (check_end(philo))
            //return (NULL);
    if (philo->s_globale->nb_philos == 1) //si y'a qu'un seul philo, il va mourir parce qu'il a une seule fourchette
    {
        ft_usleep(philo->s_globale->time_to_die);
        pthread_mutex_unlock(first_fork);
        return (NULL);
    }
    pthread_mutex_lock(second_fork);
    pthread_mutex_lock(&philo->s_globale->write_lock);
    printf("%lld %d has taken a fork\n", get_current_time(), philo->id);
    pthread_mutex_unlock(&philo->s_globale->write_lock);
    pthread_mutex_lock(&philo->s_globale->write_lock);
    printf("%lld %d is eating\n", get_current_time(), philo->id);
    pthread_mutex_unlock(&philo->s_globale->write_lock);
    pthread_mutex_lock(&philo->meal_lock);
    philo->last_meal_time = get_current_time();
    philo->nb_meals++;
    pthread_mutex_unlock(&philo->meal_lock);
    ft_usleep(philo->s_globale->time_to_eat);
    pthread_mutex_unlock(first_fork);
    pthread_mutex_unlock(second_fork);
    return (NULL);
}

//le philo lock pour pouvoir mager et unlock pour penser et dormir et laisser les autres manger
void *routine_philos(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg; //le void *arg a ete converti en pointeur de philo avec la struct t_philo rattachee
    while (1)
    {
        if (check_end(philo))
            return (NULL);
        routine_eating(arg);
        if (check_end(philo))
            return (NULL);
        pthread_mutex_lock(&philo->s_globale->write_lock);
        printf("%lld %d is sleeping\n", get_current_time(), philo->id);
        pthread_mutex_unlock(&philo->s_globale->write_lock);
        ft_usleep(philo->s_globale->time_to_sleep);
        if (check_end(philo))
            return (NULL);
        pthread_mutex_lock(&philo->s_globale->write_lock);
        printf("%lld %d is thinking\n", get_current_time(), philo->id);
        pthread_mutex_unlock(&philo->s_globale->write_lock);
    }
    return (NULL);
}
//tu check a chaque action si qql est pas mort en plein milieu
//pas d'esperluettes car left fork et right fork sont deja des pointeurs alors ont toujours l'update de l'adresse source
