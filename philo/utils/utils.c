/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:08:41 by njantsch          #+#    #+#             */
/*   Updated: 2023/08/29 19:18:55 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_data	*strct_init_data(char **av)
{
	t_data		*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (write(2, "Error: data: malloc failed\n", 30), NULL);
	data->nbr_of_philos = ft_atoi(av[1]);
	if (data->nbr_of_philos < 1)
		return (write(2, "Error: too few philosophers\n", 29), NULL);
	fork_init(data);
	data->ttdie = ft_atoi(av[2]);
	data->tteat = ft_atoi(av[3]);
	data->ttsleep = ft_atoi(av[4]);
	if (av[5] != NULL)
		data->eatcount = ft_atoi(av[5]);
	else
		data->eatcount = 0;
	gettimeofday(&data->time_of_birth, NULL);
	if (data->eatcount < 0)
		return (write(2, "Error: philos can't eat themselves\n", 36), NULL);
	strct_init_philo(data);
	if (data->philo == NULL)
		return (write(2, "Error: philo: strct_init_philo\n", 29), NULL);
	pthread_mutex_init(&data->mutex, NULL);
	pthread_mutex_init(&data->write_mutex, NULL);
	return (data);
}

void	strct_init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philos)
	{
		if (data->philo == NULL)
		{
			data->philo = malloc(sizeof(t_philos));
			if (data->philo == NULL)
				return ((void)write(2, "Error: philo: malloc failed\n", 29));
			data->philo->philosopher = NULL;
			data->philo->philo_nbr = 1;
			data->philo->time_of_last_meal = 0;
			data->philo->times_eaten = 0;
			data->philo->prev = NULL;
			data->philo->next = NULL;
		}
		else
			lst_add_new_philo(data->philo);
		i++;
	}
}

int	ft_strlen_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix && matrix[i])
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
	{
		str++;
	}
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	return (res * sign);
}

void	fork_init(t_data *data)
{
	int	i;

	i = 1;
	data->forks = malloc((data->nbr_of_philos + 1) * sizeof(int));
	while (i <= data->nbr_of_philos)
	{
		data->forks[i] = 1;
		i++;
	}
}
