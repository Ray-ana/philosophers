/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:11:11 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/06/18 16:28:25 by rzimaeva         ###   ########.fr       */
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
        
    }
    else
        exit_error("Wrong input :\nCorrect input is : ./philo 1 800 200 200 [1]");
    return (0);
}


