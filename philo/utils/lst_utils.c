/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 14:39:29 by njantsch          #+#    #+#             */
/*   Updated: 2023/08/26 18:36:52 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	lst_add_new_philo(t_philos *philo)
{
	t_philos	*curr;
	t_philos	*new_node;
	t_philos	*tmp;
	static int	nbr;

	curr = philo;
	nbr = 2;
	new_node = malloc(sizeof(t_philos));
	if (new_node == NULL)
		return ((void)write(2, "Error: add_new_philo malloc failed\n", 36));
	while (curr->next)
	{
		tmp = curr;
		curr = curr->next;
	}
	new_node->philosopher = NULL;
	new_node->philo_nbr = nbr++;
	new_node->time_of_birth = 0;
	new_node->time_of_last_meal = 0;
	new_node->forks = 1;
	new_node->prev = tmp;
	new_node->next = NULL;
	curr->next = new_node;
}

void	free_lst_philo(t_philos *lst)
{
	t_philos	*curr;
	t_philos	*tmp;

	curr = lst;
	while (curr)
	{
		tmp = curr;
		curr = curr->next;
		free(tmp);
	}
}
