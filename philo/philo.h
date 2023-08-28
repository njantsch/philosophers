/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:09:25 by njantsch          #+#    #+#             */
/*   Updated: 2023/08/28 18:14:45 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
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
	int				*forks;
	struct timeval	time_of_birth;
	struct philos	*philo;
	pthread_mutex_t	mutex;
}	t_data;

typedef struct philos
{
	pthread_t		philosopher;
	int				philo_nbr;
	int				time_of_last_meal;
	int				times_eaten;
	struct philos	*prev;
	struct philos	*next;
}	t_philos;

// utils.c
void	strct_init_philo(t_data *data);
t_data	*strct_init_data(char **av);
int		ft_strlen_matrix(char **matrix);
int		ft_atoi(const char *str);
void	fork_init(t_data *data);

// lst_utils.c
void	free_lst_philo(t_philos *lst);
void	lst_add_new_philo(t_philos *philo);

// routine_utils.c
void	take_fork_routine(t_data *curr);

// time.c
long	get_time_in_ms(struct timeval time_of_birth);
void	msleep(int time);

void	*routine(void *arg);

#endif
