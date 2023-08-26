/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 20:11:05 by njantsch          #+#    #+#             */
/*   Updated: 2023/08/26 17:19:12 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_in_ms(struct timeval time_of_birth)
{
	struct timeval	curr_time;
	long			milliseconds;

	if (gettimeofday(&curr_time, NULL) != 0)
		return (write(2, "Error: gettimeofday: failed to get time\n", 41), -1);
	milliseconds = (curr_time.tv_sec - time_of_birth.tv_sec) * CONV
		+ (curr_time.tv_usec - time_of_birth.tv_usec) / CONV;
	return (milliseconds);
}
