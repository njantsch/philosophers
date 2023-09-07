/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:29:08 by njantsch          #+#    #+#             */
/*   Updated: 2023/09/07 21:49:12 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_died(t_data *data, t_philos *philo)
{
	pthread_mutex_lock(&data->print_mutex);
	printf("%ld %d died\n", get_time_in_ms(
			data->time_of_birth), philo->philo_nbr);
	pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_lock(&data->death_mutex);
	data->death_count = 1;
	pthread_mutex_unlock(&data->death_mutex);
}

void	print_if_alive(t_data *data, t_philos *philo, char *str)
{
	pthread_mutex_lock(&data->death_mutex);
	if (data->death_count != 0)
	{
		pthread_mutex_unlock(&data->death_mutex);
		return ;
	}
	pthread_mutex_unlock(&data->death_mutex);
	pthread_mutex_lock(&data->print_mutex);
	printf("%ld %d %s\n", get_time_in_ms(
			data->time_of_birth), philo->philo_nbr, str);
	pthread_mutex_unlock(&data->print_mutex);
}

int	check_death(t_data *curr, t_philos *philos)
{
	if (get_time_in_ms(curr->time_of_birth) - philos->time_of_last_meal
		> curr->ttdie)
	{
		philo_died(curr, philos);
		pthread_mutex_unlock(&curr->time_mutex);
		return (-1);
	}
	return (0);
}
