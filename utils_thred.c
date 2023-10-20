/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_thred.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyandriy <lyandriy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:23:24 by lyandriy          #+#    #+#             */
/*   Updated: 2023/10/20 17:24:26 by lyandriy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_time(uint64_t *timer)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	*timer = ((start.tv_sec * 1000) + (start.tv_usec / 1000));
}

void	ft_usleep(uint64_t time, t_needle *needle)
{
	uint64_t	present_time;
	uint64_t	time_to_sleep;

	get_time(&present_time);
	time_to_sleep = present_time + time;
	while (time_to_sleep > present_time)
	{
		usleep(500);
		get_time(&present_time);
		if (needle->tt_die < (present_time - needle->last_meal))
		{
			if (!check_life_2(needle, present_time))
				break ;
		}
	}
}

void	print(t_needle *needle, char *str)
{
	uint64_t	timer;

	pthread_mutex_lock(&needle->common_structure->mutex_print);
	get_time(&timer);
	timer = (timer - needle->birth_time);
	if (!needle->common_structure->print_sign)
	{
		needle->common_structure->print_sign = 1;
		printf(DO, timer, (needle->my_number + 1), str);
		needle->common_structure->print_sign = 0;
	}
	pthread_mutex_unlock(&needle->common_structure->mutex_print);
}
