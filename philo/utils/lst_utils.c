/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 14:39:29 by njantsch          #+#    #+#             */
/*   Updated: 2023/08/29 19:18:29 by njantsch         ###   ########.fr       */
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
	if (nbr == 0)
		nbr++;
	new_node = malloc(sizeof(t_philos));
	if (new_node == NULL)
		return ((void)write(2, "Error: add_new_philo malloc failed\n", 36));
	while (curr->next)
	{
		tmp = curr;
		curr = curr->next;
	}
	new_node->philosopher = NULL;
	new_node->philo_nbr = ++nbr;
	new_node->time_of_last_meal = 0;
	new_node->times_eaten = 0;
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

// t_data	*reset_lst_offset(t_data *lst)
// {
// 	t_data	*curr;
// 	int		i;

// 	i = lst->nbr_of_philos;
// 	curr = lst;
// 	while (i > 1)
// 		curr->philo = curr->philo->prev;
// 	return (curr);
// }
