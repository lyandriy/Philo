/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyandriy <lyandriy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:58:23 by lyandriy          #+#    #+#             */
/*   Updated: 2023/10/18 16:44:23 by lyandriy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(t_needle *needle)
{
	print(needle, "is sleeping");
	ft_usleep(needle->tt_sleep, needle);
}

void	wait_threads(t_needle *needle)
{
	while (1)
	{
		pthread_mutex_lock(&needle->common_structure->mutex);
		if (needle->common_structure->thred_sign)
		{
			pthread_mutex_unlock(&needle->common_structure->mutex);
			break ;
		}
		pthread_mutex_unlock(&needle->common_structure->mutex);
		usleep(1);
	}
}

void	*start_routine(void *needle_original)
{
	t_needle	*needle;

	needle = (t_needle *) needle_original;
	wait_threads(needle);
	needle->last_meal = needle->birth_time;
	if (needle->my_number % 2)
		usleep(500);
	while (1)
	{
		print(needle, "is thinking");
		ft_lunch(needle);
		if(!check_dead(needle))
			break ;
		ft_sleep(needle);
	}
	return (NULL);
}
