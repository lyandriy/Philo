/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_or_dead.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyandriy <lyandriy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:40:16 by lyandriy          #+#    #+#             */
/*   Updated: 2023/10/11 17:30:47 by lyandriy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_needle *needle)
{
	pthread_mutex_lock(&needle->struct_dead->mutex);
	if (needle->struct_dead->death_sign == 1)
	{
		pthread_mutex_unlock(&needle->struct_dead->mutex);
		return (0);
	}
	pthread_mutex_unlock(&needle->struct_dead->mutex);
	return (1);
}

int	check_life(t_needle *needle)
{
	uint64_t	timer;

	get_time(&timer);
	if (needle->last_meal == 0)
		needle->last_meal = needle->birth_time;
	if (needle->tt_die < (timer - needle->last_meal))
	{
		if (check_dead(needle))
		{
			pthread_mutex_lock(&needle->struct_dead->mutex);
			needle->struct_dead->death_sign = 1;
			pthread_mutex_unlock(&needle->struct_dead->mutex);
			print(needle, "died uwu", 0);
		}
		return (0);
	}
	return (1);
}
