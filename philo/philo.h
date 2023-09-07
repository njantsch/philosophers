/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:09:25 by njantsch          #+#    #+#             */
/*   Updated: 2023/09/07 21:49:21 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>
# include <pthread.h>
# include <string.h>

# define CONV 1000

typedef struct data
{
	int				nbr_of_philos;
	int				tteat;
	int				ttsleep;
	int				ttdie;
	int				eatcount;
	int				death_count;
	struct timeval	time_of_birth;
	struct philos	*philo;
	pthread_t		death;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	time_mutex;
	pthread_mutex_t	*forks;
}	t_data;

typedef struct philos
{
	pthread_t		philosopher;
	int				philo_nbr;
	long			time_of_last_meal;
	int				times_eaten;
	struct philos	*next;
}	t_philos;

// main.c
void	mutex_init(t_data *data);

// utils.c
void	strct_init_philo(t_data *data);
t_data	*strct_init_data(char **av);
int		ft_strlen_matrix(char **matrix);
int		ft_atoi(const char *str);

// lst_utils.c
void	free_lst_philo(t_philos *lst);
void	lst_add_new_philo(t_philos *philo);

// time.c
long	get_time_in_ms(struct timeval time_of_birth);
void	msleep(int time);

// routines.c
int		take_fork_routine(t_data *curr, t_philos *philo);
int		eating_routine(t_data *curr, t_philos *philo);
void	*routine(void *arg);
void	*death_routine(void *arg);

// routine_utils.c
void	print_if_alive(t_data *data, t_philos *philo, char *str);
void	philo_died(t_data *data, t_philos *philo);
int		check_death(t_data *curr, t_philos *philos);

// checks.c
int		check_input(int ac, char **av);

#endif
