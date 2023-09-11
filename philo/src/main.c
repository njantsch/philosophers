/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:13:43 by njantsch          #+#    #+#             */
/*   Updated: 2023/09/11 12:18:11 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	mutex_init(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->time_mutex, NULL);
	if (pthread_mutex_init(&data->print_mutex, NULL) == -1)
		return ((void)pthread_mutex_destroy(&data->time_mutex));
	if (pthread_mutex_init(&data->death_mutex, NULL) == -1)
		return ((void)pthread_mutex_destroy(&data->time_mutex),
			(void)pthread_mutex_destroy(&data->print_mutex));
	if (pthread_mutex_init(&data->philo_mutex, NULL) == -1)
		return ((void)pthread_mutex_destroy(&data->time_mutex),
			(void)pthread_mutex_destroy(&data->print_mutex),
			(void)pthread_mutex_destroy(&data->death_mutex));
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
	pthread_mutex_destroy(&data->philo_mutex);
	while (i < data->nbr_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}

int	thread_loop(t_data *curr)
{
	while (curr->philo)
	{
		if (pthread_create(&curr->philo->philosopher, NULL,
				&routine, (void *)curr) != 0)
			return (write(2, "Error: failed to create thread\n", 31), -1);
		usleep(50);
		pthread_mutex_lock(&curr->philo_mutex);
		if (!curr->philo->next)
		{
			pthread_mutex_unlock(&curr->philo_mutex);
			break ;
		}
		curr->philo = curr->philo->next;
		pthread_mutex_unlock(&curr->philo_mutex);
	}
	return (0);
}

void	create_threads(t_data *data)
{
	t_data		*curr;
	t_philos	*reset;

	reset = data->philo;
	curr = data;
	if (pthread_create(&data->death, NULL, &death_routine, (void *)data) != 0)
		return ((void)write(2, "Error: failed to create death thread\n", 37));
	thread_loop(curr);
	if (pthread_join(data->death, NULL) != 0)
		write(2, "Error: failed to join death thread\n", 35);
	while (reset)
	{
		if (pthread_join(reset->philosopher, NULL) != 0)
			write(2, "Error: failed to join philo thread\n", 35);
		reset = reset->next;
	}
}

int	main(int ac, char **av)
{
	t_data		*data;
	t_philos	*reset;

	if (ac < 5 || ac > 6)
		return (write(2, "Error: wrong amount of arguments\n", 33), 1);
	if (check_input(ac, av) == -1)
		return (1);
	data = strct_init_data(av);
	if (data == NULL)
		return (1);
	reset = data->philo;
	create_threads(data);
	mutex_destroy(data);
	free_lst_philo(reset);
	free(data->forks);
	free(data);
	return (0);
}
