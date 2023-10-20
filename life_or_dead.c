/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_or_dead.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyandriy <lyandriy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:40:16 by lyandriy          #+#    #+#             */
/*   Updated: 2023/10/20 17:48:45 by lyandriy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_needle *needle)
{
	pthread_mutex_lock(&needle->common_structure->mutex);
	if (needle->common_structure->death_sign == 1)
	{
		pthread_mutex_unlock(&needle->common_structure->mutex);
		return (0);
	}
	pthread_mutex_unlock(&needle->common_structure->mutex);
	return (1);
}

int	check_life(t_needle *needle)
{
	uint64_t	timer;

	get_time(&timer);
	if (needle->tt_die < (timer - needle->last_meal))
	{
		pthread_mutex_lock(&needle->common_structure->mutex);
		if (needle->common_structure->death_sign == 0)
		{
			needle->common_structure->death_sign = 1;
			needle->common_structure->time_die = (timer - needle->birth_time);
			needle->common_structure->numb_philo = needle->my_number;
		}
		pthread_mutex_unlock(&needle->common_structure->mutex);
		return (0);
	}
	return (1);
}

int	check_life_2(t_needle *needle, uint64_t present_time)
{
	pthread_mutex_lock(&needle->common_structure->mutex);
	if (needle->common_structure->death_sign == 0)
	{
		needle->common_structure->death_sign = 1;
		needle->common_structure->time_die
			= (present_time - needle->birth_time);
		needle->common_structure->numb_philo = needle->my_number;
		return (0);
	}
	pthread_mutex_unlock(&needle->common_structure->mutex);
	return (1);
}
