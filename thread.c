/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyandriy <lyandriy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:58:23 by lyandriy          #+#    #+#             */
/*   Updated: 2023/10/15 20:00:56 by lyandriy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(t_needle *needle)
{
	the_logs(needle, "is sleeping", 4);
	ft_usleep(needle->tt_sleep, needle);
}

int	wait_threads(t_needle *needle)
{
		pthread_mutex_lock(&needle->common_structure->mutex);
		if (!needle->common_structure->thred_sign)
		{
			pthread_mutex_unlock(&needle->common_structure->mutex);
			return (0);
		}
		pthread_mutex_unlock(&needle->common_structure->mutex);
		return (1);
}

void	*start_routine(void *needle_original)
{
	t_needle	*needle;

	needle = (t_needle *) needle_original;
	while (!wait_threads(needle))
	{
	}
	needle->last_meal = needle->birth_time;
	if (needle->my_number % 2)
		usleep(500);
	while (1)
	{
		the_logs(needle, "is thinking", 1);
		ft_lunch(needle);
		ft_sleep(needle);
		if(!check_dead(needle))
		{
			printf("hola\n");
			break ;
		}
	}
	return (NULL);
}
