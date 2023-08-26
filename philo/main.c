/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:13:43 by njantsch          #+#    #+#             */
/*   Updated: 2023/08/26 18:45:58 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	int		time;
	t_data	*curr;

	curr = (t_data *)arg;
	while (1)
	{
		if (curr->philo == NULL)
			curr = (t_data *)arg;
		if (curr->philo->times_eaten >= curr->eatcount)
			break ;
		pthread_mutex_lock(&curr->mutex);
		time = get_time_in_ms(curr->philo->time_of_birth);
		printf("%d %d has taken a fork\n", time, curr->philo->philosopher);
	}
	return (NULL);
}

void	create_threads(t_data *data)
{
	pthread_mutex_t	mutex;
	t_data			*curr;
	struct timeval	current_time;

	curr = data;
	pthread_mutex_init(&mutex, NULL);
	curr->mutex = mutex;
	while (curr->philo)
	{
		curr->philo->time_of_birth = gettimeofday(current_time);
		if (pthread_create(&curr->philo->philosopher, NULL,
				&routine, (void *)curr) != 0)
			return ((void)write(2, "Error: failed to create thread\n", 32));
		usleep(50);
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
	free_lst_philo(data->philo);
	free(data);
	return (0);
}
