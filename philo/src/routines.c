/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:10:46 by njantsch          #+#    #+#             */
/*   Updated: 2023/09/07 21:58:23 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*death_routine(void *arg)
{
	t_data		*curr;
	t_philos	*philos;
	t_philos	*reset;

	curr = (t_data *)arg;
	reset = curr->philo;
	philos = reset;
	while (1)
	{
		if (philos->philo_nbr == curr->nbr_of_philos
			&& curr->nbr_of_philos > 1)
			philos = reset;
		pthread_mutex_lock(&curr->time_mutex);
		if (philos->times_eaten == curr->eatcount && curr->eatcount > 0)
			return (pthread_mutex_unlock(&curr->time_mutex), NULL);
		pthread_mutex_unlock(&curr->time_mutex);
		pthread_mutex_lock(&curr->time_mutex);
		if (check_death(curr, philos) == -1)
			break ;
		pthread_mutex_unlock(&curr->time_mutex);
		if (curr->nbr_of_philos > 1)
			philos = philos->next;
	}
	return (NULL);
}

int	take_fork_routine(t_data *curr, t_philos *philo)
{
	if (philo->philo_nbr == curr->nbr_of_philos - 1)
	{
		pthread_mutex_lock(&curr->forks[philo->philo_nbr
			% curr->nbr_of_philos]);
		pthread_mutex_lock(&curr->forks[philo->philo_nbr - 1]);
	}
	else
	{
		pthread_mutex_lock(&curr->forks[philo->philo_nbr - 1]);
		if (curr->nbr_of_philos == 1)
			return (pthread_mutex_unlock(
					&curr->forks[philo->philo_nbr - 1]), -1);
		pthread_mutex_lock(&curr->forks[philo->philo_nbr
			% curr->nbr_of_philos]);
	}
	print_if_alive(curr, philo, "has taken a fork");
	print_if_alive(curr, philo, "has taken a fork");
	return (0);
}

int	eating_routine(t_data *curr, t_philos *philo)
{
	if (take_fork_routine(curr, philo) == -1)
		return (print_if_alive(curr, philo, "has taken a fork"), -1);
	print_if_alive(curr, philo, "is eating");
	msleep(curr->tteat);
	pthread_mutex_lock(&curr->time_mutex);
	philo->time_of_last_meal = get_time_in_ms(curr->time_of_birth);
	philo->times_eaten += 1;
	pthread_mutex_unlock(&curr->time_mutex);
	if (philo->philo_nbr == curr->nbr_of_philos - 1)
	{
		pthread_mutex_unlock(&curr->forks[philo->philo_nbr
			% curr->nbr_of_philos]);
		pthread_mutex_unlock(&curr->forks[philo->philo_nbr - 1]);
	}
	else
	{
		pthread_mutex_unlock(&curr->forks[philo->philo_nbr - 1]);
		pthread_mutex_unlock(&curr->forks[philo->philo_nbr
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
		pthread_mutex_lock(&curr->death_mutex);
		if (curr->death_count != 0)
		{
			pthread_mutex_unlock(&curr->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&curr->death_mutex);
		print_if_alive(curr, philo, "is sleeping");
		msleep(curr->ttsleep);
		print_if_alive(curr, philo, "is thinking");
		if (curr->nbr_of_philos % 2 != 0)
			msleep(curr->tteat * 2 - curr->ttsleep);
	}
	return (NULL);
}
