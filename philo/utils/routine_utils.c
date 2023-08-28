/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:10:46 by njantsch          #+#    #+#             */
/*   Updated: 2023/08/28 19:11:40 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_fork_routine(t_data *curr)
{
	if (curr->philo->philo_nbr == 1)
		if (curr->forks[curr->nbr_of_philos] == 0
			|| curr->forks[1] == 0)
			while (1)
				if (curr->forks[curr->nbr_of_philos] == 1
					&& curr->forks[1] == 1)
					break ;
	if ((curr->forks[curr->philo->philo_nbr - 1] == 0
		|| curr->forks[curr->philo->philo_nbr] == 0)
		&& curr->philo->philo_nbr != 1)
			while (1)
				if (curr->forks[curr->philo->philo_nbr - 1] == 1
					&& curr->forks[curr->philo->philo_nbr] == 1)
					break ;
	if (curr->philo->philo_nbr == 1)
		curr->forks[curr->nbr_of_philos] = 0;
	else
		curr->forks[curr->philo->philo_nbr - 1] = 0;
	printf("%ld %d has taken a fork\n", get_time_in_ms(
			curr->time_of_birth), curr->philo->philo_nbr);
	if (curr->philo->philo_nbr == curr->nbr_of_philos)
		curr->forks[1] = 0;
	else
		curr->forks[curr->philo->philo_nbr] = 0;
	printf("%ld %d has taken a fork\n", get_time_in_ms(
			curr->time_of_birth), curr->philo->philo_nbr);
}
