/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:10:46 by njantsch          #+#    #+#             */
/*   Updated: 2023/08/29 21:12:26 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork_routine(t_data *curr, t_philos *philo)
{
	if (philo->philo_nbr == 1)
		if (curr->forks[curr->nbr_of_philos] == 0
			|| curr->forks[1] == 0)
			while (1)
				if (curr->forks[curr->nbr_of_philos] == 1
					&& curr->forks[1] == 1)
					break ;
	if ((curr->forks[philo->philo_nbr - 1] == 0
		|| curr->forks[philo->philo_nbr] == 0)
		&& philo->philo_nbr != 1)
		while (1)
			if (curr->forks[philo->philo_nbr - 1] == 1
				&& curr->forks[philo->philo_nbr] == 1)
				break ;
	pthread_mutex_lock(&curr->mutex);
	if (philo->philo_nbr == 1)
		curr->forks[curr->nbr_of_philos] = 0;
	else
		curr->forks[philo->philo_nbr - 1] = 0;
	pthread_mutex_lock(&curr->write_mutex);
	printf("%ld %d has taken a fork\n", get_time_in_ms(
			curr->time_of_birth), philo->philo_nbr);
	pthread_mutex_unlock(&curr->write_mutex);
	pthread_mutex_unlock(&curr->mutex);
	pthread_mutex_lock(&curr->mutex);
	if (philo->philo_nbr == curr->nbr_of_philos)
		curr->forks[1] = 0;
	else
		curr->forks[philo->philo_nbr] = 0;
	pthread_mutex_lock(&curr->write_mutex);
	printf("%ld %d has taken a fork\n", get_time_in_ms(
			curr->time_of_birth), philo->philo_nbr);
	pthread_mutex_unlock(&curr->write_mutex);
	pthread_mutex_unlock(&curr->mutex);
}

int	eating_routine(t_data *curr, t_philos *philo)
{
	if (philo->times_eaten >= curr->eatcount && curr->eatcount > 0)
		return (-1);
	take_fork_routine(curr, philo);
	pthread_mutex_lock(&curr->write_mutex);
	printf("%ld %d is eating\n", get_time_in_ms(
		curr->time_of_birth), philo->philo_nbr);
	pthread_mutex_unlock(&curr->write_mutex);
	usleep(curr->tteat * CONV);
	pthread_mutex_lock(&curr->mutex);
	philo->times_eaten += 1;
	if (philo->philo_nbr == 1)
		curr->forks[curr->nbr_of_philos] = 1;
	else
		curr->forks[philo->philo_nbr - 1] = 1;
	if (philo->philo_nbr == curr->nbr_of_philos)
		curr->forks[1] = 1;
	else
		curr->forks[philo->philo_nbr] = 1;
	pthread_mutex_unlock(&curr->mutex);
	return (0);
}

void	*routine(void *arg)
{
	t_data		*curr;
	t_philos	*philo;

	curr = (t_data *)arg;
	philo = curr->philo;
	while (1)
	{
		if (eating_routine(curr, philo) == -1)
			break ;
		pthread_mutex_lock(&curr->write_mutex);
		printf("%ld %d is sleeping\n", get_time_in_ms(
			curr->time_of_birth), philo->philo_nbr);
		pthread_mutex_unlock(&curr->write_mutex);
		usleep(curr->ttsleep * CONV);
	}
	return (NULL);
}
