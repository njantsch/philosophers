/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 20:18:41 by njantsch          #+#    #+#             */
/*   Updated: 2023/09/07 21:46:38 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

long	ft_atol(const char *str)
{
	long	res;
	int		sign;

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

int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (((str[i] > '9' || str[i] < '0') && str[i] != '-' && str[i] != '+')
			|| (i != 0 && str[i] == '+'))
			return (write(2, "Error: arguments must be numbers\n", 33), -1);
		i++;
	}
	if (ft_strlen(str) == 0)
		return (write(2, "Error: argument is empty\n", 25), -1);
	return (0);
}

int	ft_number_check(char *str)
{
	int	num;

	if (ft_atol(str) > INT_MAX)
		return (write(2, "Error: over INT_MAX is not supported\n", 37), -1);
	if (ft_atol(str) < INT_MIN)
		return (write(2, "Error: arguments must be positive\n", 34), -1);
	num = ft_atoi(str);
	if (num < 0)
		return (write(2, "Error: arguments must be positive\n", 34), -1);
	if (num == 0)
		return (write(2, "Error: number has to be 1 or larger\n", 37), -1);
	return (0);
}

int	check_input(int ac, char **av)
{
	int	i;
	int	len;

	i = 1;
	if (ac == 5)
		len = 5;
	else
		len = 6;
	while (i < len)
	{
		if (ft_isdigit(av[i]) == -1)
			return (-1);
		if (ft_number_check(av[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}
