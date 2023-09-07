/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 20:11:05 by njantsch          #+#    #+#             */
/*   Updated: 2023/09/05 12:15:46 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	get_time_in_ms(struct timeval time_of_birth)
{
	struct timeval	curr_time;
	long			ms;

	if (gettimeofday(&curr_time, NULL) != 0)
		return (write(2, "Error: gettimeofday: failed to get time\n", 41), -1);
	ms = (curr_time.tv_sec - time_of_birth.tv_sec) * CONV
		+ (curr_time.tv_usec - time_of_birth.tv_usec) / CONV;
	return (ms);
}

void	msleep(int time)
{
	long			curr_time;
	struct timeval	zero_time;

	zero_time.tv_sec = 0;
	zero_time.tv_usec = 0;
	curr_time = get_time_in_ms(zero_time);
	while ((get_time_in_ms(zero_time) - curr_time) < time)
		usleep(500);
}
