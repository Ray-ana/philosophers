/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 13:38:21 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/04/28 14:49:30 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

tas heap partage genre tous les threads dans le stacks sont dedans 


#include <pthread.h>

pour compiler on utilise -lpthread (-l pour lier avec la biblotheque pthread, comme le -I . qui indique le chemin ou se situe le .h)

on utilise un thread pour lui assigner une tache specifique pendant qu'on fait autre chose

on utilise toujours *void car la bibliotheque pthread est generique  