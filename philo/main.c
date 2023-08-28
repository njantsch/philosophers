/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:13:43 by njantsch          #+#    #+#             */
/*   Updated: 2023/08/28 19:09:02 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating_routine(t_data *curr)
{
	if (curr->philo->times_eaten >= curr->eatcount && curr->eatcount > 0)
		return (-1);
	take_fork_routine(curr);
	printf("%ld %d is eating\n", get_time_in_ms(
			curr->time_of_birth), curr->philo->philo_nbr);
	usleep(curr->tteat * CONV);
	curr->philo->times_eaten++;
	if (curr->philo->philo_nbr == 1)
		curr->forks[curr->nbr_of_philos] = 1;
	else
		curr->forks[curr->philo->philo_nbr - 1] = 1;
	if (curr->philo->philo_nbr == curr->nbr_of_philos)
		curr->forks[1] = 1;
	else
		curr->forks[curr->philo->philo_nbr] = 1;
	return (0);
}

void	*routine(void *arg)
{
	t_data	*curr;

	curr = (t_data *)arg;
	while (1)
	{
		if (eating_routine(curr) == -1)
			break ;
	}
	return (NULL);
}

void	create_threads(t_data *data)
{
	pthread_mutex_t	mutex;
	t_data			*curr;

	curr = data;
	pthread_mutex_init(&mutex, NULL);
	curr->mutex = mutex;
	while (curr->philo)
	{
		if (pthread_create(&curr->philo->philosopher, NULL,
				&routine, (void *)curr) != 0)
			return ((void)write(2, "Error: failed to create thread\n", 32));
		sleep(1);
		curr->philo = curr->philo->next;
	}
	curr = data;
	while (curr->philo)
	{
		if (pthread_join(curr->philo->philosopher, NULL) != 0)
			return ((void)write(2, "Error; failed to join thread\n", 30));
		curr->philo = curr->philo->next;
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
	pthread_mutex_destroy(&data->mutex);
	free_lst_philo(data->philo);
	free(data->forks);
	free(data);
	return (0);
}
