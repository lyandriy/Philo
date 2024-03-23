/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyandriy <lyandriy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:58:23 by lyandriy          #+#    #+#             */
/*   Updated: 2023/10/28 17:17:12 by lyandriy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(t_needle *needle)
{
	print(needle, "is sleeping");
	ft_usleep(needle->tt_sleep, needle);
}

int	wait_threads(t_needle *needle)
{
	while (1)
	{
		pthread_mutex_lock(&needle->common_structure->mutex);
		if (needle->common_structure->thred_sign)
		{
			pthread_mutex_unlock(&needle->common_structure->mutex);
			return (1);
		}
		pthread_mutex_unlock(&needle->common_structure->mutex);
		usleep(100);
	}
}

int	check_number_of_meals(t_needle *needle)
{
	if (needle->must_eat)
	{
		pthread_mutex_lock(&needle->common_structure->eat);
		if (needle->number_of_meals == needle->must_eat)
			needle->common_structure->philosopher_eat++;
		if (needle->common_structure->philosopher_eat == needle->num_ph)
		{
			pthread_mutex_unlock(&needle->common_structure->eat);
			return (0);
		}
		pthread_mutex_unlock(&needle->common_structure->eat);
	}
	return (1);
}

void	*start_routine(void *needle_original)
{
	t_needle	*needle;

	needle = (t_needle *) needle_original;
	if (!wait_threads(needle))
		return (NULL);
	get_time(&needle->birth_time);
	needle->last_meal = needle->birth_time;
	if (needle->my_number % 2)
		usleep(500);
	while (1)
	{
		print(needle, "is thinking");
		ft_lunch(needle);
		if (!check_dead(needle))
			break ;
		ft_sleep(needle);
		if (!check_number_of_meals(needle))
			break ;
	}
	return (NULL);
}
