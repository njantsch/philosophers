/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:08:41 by njantsch          #+#    #+#             */
/*   Updated: 2023/09/08 17:47:39 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_data	*strct_init_data(char **av)
{
	t_data		*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (write(2, "Error: data: malloc failed\n", 27), NULL);
	data->nbr_of_philos = ft_atoi(av[1]);
	data->ttdie = ft_atoi(av[2]);
	data->tteat = ft_atoi(av[3]);
	data->ttsleep = ft_atoi(av[4]);
	data->death_count = 0;
	if (av[5] != NULL)
		data->eatcount = ft_atoi(av[5]);
	else
		data->eatcount = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_of_philos);
	if (!data->forks)
		return (write(2, "Error: forks: malloc failed\n", 28), NULL);
	gettimeofday(&data->time_of_birth, NULL);
	data->philo = NULL;
	strct_init_philo(data);
	if (data->philo == NULL)
		return (write(2, "Error: philo: strct_init_philo\n", 29), NULL);
	mutex_init(data);
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
			data->philo->philo_nbr = 1;
			data->philo->time_of_last_meal = 0;
			data->philo->times_eaten = 0;
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
	while (*str == '-' || *str == '+')
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
