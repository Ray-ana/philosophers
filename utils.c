/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:11:05 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/06/18 15:51:50 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	nb_args(int ac, char **av)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (ac < 5 || ac > 6)
		return (0);
	i = 1;
	while (i < ac) // il verifie si chaque arg est bon
	{
		j = 0;
		while (av[i][j]) // si cest pas une numero on arrete
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}


int ft_atoi(char *str)
{
	int i;
    int sign;
    long long res;
	
    i = 0;
    sign = 1;
    res = 0;
    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
	i++;
    if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		if (res > 2147483647)
		return (-1);
		i++;
	}
	return (res * sign);
}

void error_exit(const char *error)
{
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
