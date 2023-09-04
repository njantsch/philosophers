/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:13:43 by njantsch          #+#    #+#             */
/*   Updated: 2023/09/04 19:27:51 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_init(t_data *data)
{
	int	i;

	i = 1;
	pthread_mutex_init(&data->mutex, NULL);
	pthread_mutex_init(&data->mutex2, NULL);
	while (i <= data->nbr_of_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

void	mutex_destroy(t_data *data)
{
	int	i;

	i = 1;
	pthread_mutex_destroy(&data->mutex);
	pthread_mutex_destroy(&data->mutex2);
	while (i <= data->nbr_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}

void	create_threads(t_data *data)
{
	t_data		*curr;
	t_philos	*reset;

	reset = data->philo;
	curr = data;
	while (curr->philo)
	{
		if (pthread_create(&curr->philo->philosopher, NULL,
				&routine, (void *)curr) != 0)
			return ((void)write(2, "Error: failed to create thread\n", 32));
		usleep(50);
		if (!curr->philo->next)
			break ;
		curr->philo = curr->philo->next;
	}
	while (reset)
	{
		if (pthread_join(reset->philosopher, NULL) != 0)
			return ((void)write(2, "Error; failed to join thread\n", 30));
		reset = reset->next;
	}
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac < 5 || ac > 6)
		return (write(2, "Error: wrong amount of arguments\n", 34), 1);
	data = strct_init_data(av);
	if (data == NULL)
		return (1);
	create_threads(data);
	mutex_destroy(data);
	free_lst_philo(data->philo);
	free(data);
	return (0);
}
