/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:09:25 by njantsch          #+#    #+#             */
/*   Updated: 2023/08/26 18:30:20 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define CONV 1000

typedef struct data
{
	int				nbr_of_philos;
	int				tteat;
	int				ttsleep;
	int				ttdie;
	int				eatcount;
	struct philos	*philo;
	// struct timeval	curr;
	pthread_mutex_t	mutex;
}	t_data;

typedef struct philos
{
	pthread_t		philosopher;
	int				philo_nbr;
	struct timeval	time_of_birth;
	int				time_of_last_meal;
	int				times_eaten;
	int				forks;
	struct philos	*prev;
	struct philos	*next;
}	t_philos;

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

void	*routine(void *arg);

#endif
