/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:11:02 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/06/30 18:08:13 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_struct_globale	t_struct_globale;

typedef struct s_philo
{
	int							id;
	int							current_meals;
	long long					last_meal_time;
	pthread_t					thread;
	pthread_mutex_t				*left_fork;
	pthread_mutex_t				*right_fork;
	pthread_mutex_t				meal_lock;
	t_struct_globale			*s_globale;
}								t_philo;
// meal_lock pour que le monitor puisse lire nb_meals et
// last_meal_time sans data race

typedef struct s_struct_globale
{
	long long					nb_philos;
	long long					time_to_eat;
	long long					time_to_die;
	long long					time_to_sleep;
	int							max_meals;
	long long					start_time;
	bool						end;
	pthread_t					monitor;
	pthread_mutex_t				write_lock;
	pthread_mutex_t				dead_lock;
	pthread_mutex_t				*fork_lock;
	t_philo						*philo;
}								t_struct_globale;

// Main
int								launch_threads(t_struct_globale *data);

// Monitoring
void							*monitor_routine(void *arg);
int								check_on_philos(t_struct_globale *data,
									int *done_eating);

// Init
int								init_mutex(t_struct_globale *data);
void							destroy_mutex(t_struct_globale *data);
int								init_data(t_struct_globale *data, int ac,
									char **av);
int								alloc_data(t_struct_globale *data);
void							init_forks(t_struct_globale *data);

// Routine
void							print_text(char *str, t_philo *philo, int id);
void							*eating(t_philo *philo);
void							sleeping(t_philo *philo);
void							thinking(t_philo *philo);
void							*routine_philos(void *arg);

// Utils
int								check_end(t_philo *philo);
long long						get_current_time(void);
void							ft_usleep(long long time_in_ms);
int								nb_args(int ac, char **av);
int								ft_atoi(char *str);

#endif