/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:11:11 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/06/18 14:00:52 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
    t_struct_globale info;

    if (ac == 5 || ac == 6)
    {
        if (nb_args(ac, av) == 0) //== 0 si elle renvoie 0, le cas d'erreur
        {
            printf("Error: Arguments must be integers\n");
            return (1);
        }
        if (init_info(&info, ac, av) == 0)
        {
            return (0);
        }
        grjtergrhred
    }
    else
        exit_error("Wrong input :\nCorrect input is : ./philo 1 800 200 200 [1]");
    return (0);
}

int alloc_info(t_struct_globale *info)
{
    info->philos = malloc(sizeof(t_philo) * (info->nb_philos)); //qund tu sizeof tu mets le type
    info->fork_lock = malloc(sizeof(pthread_mutex_t) * (info->nb_philos)); //nb_philos car il y a le meme nombre de fourchettes que de philos

    if (!info->philos || !info->fork_lock)
    {
        if (info->philos)
            free(info->philos);
        if (info->fork_lock)
            free(info->fork_lock);
        return (0);
    }
    return (1);
}
