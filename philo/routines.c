/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:10:46 by njantsch          #+#    #+#             */
/*   Updated: 2023/09/04 19:46:41 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork_routine(t_data *curr, t_philos *philo)
{
	if (philo->philo_nbr == curr->nbr_of_philos - 1)
	{
		pthread_mutex_lock(&curr->forks[philo->philo_nbr
		% curr->nbr_of_philos + 1]);
		pthread_mutex_lock(&curr->forks[philo->philo_nbr]);
	}
	else
	{
		pthread_mutex_lock(&curr->forks[philo->philo_nbr]);
		pthread_mutex_lock(&curr->forks[(philo->philo_nbr + 1)
		% curr->nbr_of_philos]);
	}
	pthread_mutex_lock(&curr->mutex);
	printf("%ld %d has taken a fork\n", get_time_in_ms(
			curr->time_of_birth), philo->philo_nbr);
	pthread_mutex_unlock(&curr->mutex);
	pthread_mutex_lock(&curr->mutex2);
	printf("%ld %d has taken a fork\n", get_time_in_ms(
			curr->time_of_birth), philo->philo_nbr);
	pthread_mutex_unlock(&curr->mutex2);
}

int	eating_routine(t_data *curr, t_philos *philo)
{
	take_fork_routine(curr, philo);
	pthread_mutex_lock(&curr->mutex);
	printf("%ld %d is eating\n", get_time_in_ms(
		curr->time_of_birth), philo->philo_nbr);
	pthread_mutex_unlock(&curr->mutex);
	msleep(curr->tteat);
	philo->time_of_last_meal = get_time_in_ms(curr->time_of_birth);
	philo->times_eaten += 1;
	if (philo->philo_nbr == curr->nbr_of_philos - 1)
	{
		pthread_mutex_unlock(&curr->forks[philo->philo_nbr
		% curr->nbr_of_philos + 1]);
		pthread_mutex_unlock(&curr->forks[philo->philo_nbr]);
	}
	else
	{
		pthread_mutex_unlock(&curr->forks[philo->philo_nbr]);
		pthread_mutex_unlock(&curr->forks[(philo->philo_nbr + 1)
		% curr->nbr_of_philos]);
	}
	if (philo->times_eaten >= curr->eatcount && curr->eatcount > 0)
		return (-1);
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
		pthread_mutex_lock(&curr->mutex2);
		printf("%ld %d is sleeping\n", get_time_in_ms(
			curr->time_of_birth), philo->philo_nbr);
		pthread_mutex_unlock(&curr->mutex2);
		msleep(curr->ttsleep);
		pthread_mutex_lock(&curr->mutex);
		printf("%ld %d is thinking\n", get_time_in_ms(
			curr->time_of_birth), philo->philo_nbr);
		pthread_mutex_unlock(&curr->mutex);
		msleep(curr->tteat * 2 - curr->ttsleep);
	}
	return (NULL);
}
