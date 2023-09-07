/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:13:43 by njantsch          #+#    #+#             */
/*   Updated: 2023/09/07 21:21:20 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	mutex_init(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->time_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	while (i < data->nbr_of_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

void	mutex_destroy(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->time_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	while (i < data->nbr_of_philos)
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
	if (pthread_create(&data->death, NULL, &death_routine, (void *)data) != 0)
		return ((void)write(2, "Error: failed to create death thread\n", 37));
	while (curr->philo)
	{
		if (pthread_create(&curr->philo->philosopher, NULL,
				&routine, (void *)curr) != 0)
			return ((void)write(2, "Error: failed to create thread\n", 31));
		usleep(50);
		if (!curr->philo->next)
			break ;
		curr->philo = curr->philo->next;
	}
	if (pthread_join(data->death, NULL) != 0)
		return ((void)write(2, "Error: failed to join death thread\n", 35));
	while (reset)
	{
		if (pthread_join(reset->philosopher, NULL) != 0)
			return ((void)write(2, "Error: failed to join philo thread\n", 35));
		reset = reset->next;
	}
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac < 5 || ac > 6)
		return (write(2, "Error: wrong amount of arguments\n", 34), 1);
	if (check_input(ac, av) == -1)
		return (1);
	data = strct_init_data(av);
	if (data == NULL)
		return (1);
	create_threads(data);
	mutex_destroy(data);
	free_lst_philo(data->philo);
	free(data->forks);
	free(data);
	return (0);
}
