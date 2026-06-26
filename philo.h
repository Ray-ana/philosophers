/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:11:02 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/06/26 21:38:54 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/time.h>
#include <stdbool.h>

typedef struct s_struct_globale t_struct_globale; //c'est juste pour que les struct voient que ca existe

typedef struct s_philo
{
    int id; //si c'est philo 1, 2, 3 ou 4
    int nb_meals; //combien de fois il a mange
    long long last_meal_time; //long long parce qu'on doit manipuler des microsecondes avec le gettimeofday
    pthread_t thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t meal_lock; //pour que le moniteur puisse lire nb_meals et last_meal_time sans data race
    t_struct_globale *s_globale;
}   t_philo;

typedef struct s_struct_globale
{
    long long nb_philos;
    long long time_to_eat;
    long long time_to_die;
    long long time_to_sleep;
    int max_meals;
    long long start_time; //quand on lance la simulation
    bool end; //que en 0 ou en 1 donc pas besoin de long long
    pthread_t   monitor;
    pthread_mutex_t write_lock;
    pthread_mutex_t dead_lock;
    pthread_mutex_t *fork_lock; //empeche les philos de prendre la meme fourchette
    t_philo *philo; //on va stocker la memoire ici
}   t_struct_globale;

// Utils
int     nb_args(int ac, char **av);
int     ft_atoi(char *str);
void    exit_error(const char *error);
void	free_tab(char **tab);
void    ft_usleep(long long time_in_ms);

// Parsing
int     init_info(t_struct_globale *info, int ac, char **av);
int     alloc_info(t_struct_globale *info);

// Mutex
int init_mutex(t_struct_globale *info);
void init_forks(t_struct_globale *info);
void    launch_threads(t_struct_globale *info);
void *routine_philos(void *arg);
void    destroy_mutex(t_struct_globale *info);


#endif
//mutex c'est un lock, il verouille un thread pour qu'un autre fasse sa propre tache