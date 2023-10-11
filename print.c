/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyandriy <lyandriy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:37:06 by lyandriy          #+#    #+#             */
/*   Updated: 2023/10/11 18:49:49 by lyandriy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_dead(t_needle *needle, char *str, int flag)
{
	uint64_t	timer;

	if (!check_dead(needle) && !flag)
	{
		pthread_mutex_lock(&needle->struct_dead->mutex);
		if (needle->struct_dead->print_sign == -1)
		{
			needle->struct_dead->print_sign = needle->my_number;
			pthread_mutex_lock(&needle->mutex);
			get_time(&timer);
			timer = (timer - needle->birth_time);
			printf(DEAD, timer, (needle->my_number + 1), str);
			pthread_mutex_unlock(&needle->mutex);
		}
		pthread_mutex_unlock(&needle->struct_dead->mutex);
	}
}

void	print_logs(t_needle *needle, char *str, int flag)
{
	uint64_t	timer;

	if (flag && check_dead(needle))
	{
		pthread_mutex_lock(&needle->struct_dead->mutex);
		if (needle->struct_dead->print_sign == -1)
		{
			pthread_mutex_lock(&needle->mutex);
			get_time(&timer);
			timer = (timer - needle->birth_time);
			if (flag == 1)
				printf(THINK, timer, (needle->my_number + 1), str);
			if (flag == 2)
				printf(FORK, timer, (needle->my_number + 1), str);
			if (flag == 3)
				printf(EATING, timer, (needle->my_number + 1), str);
			if (flag == 4)
				printf(SLEEP, timer, (needle->my_number + 1), str);
			pthread_mutex_unlock(&needle->mutex);
		}
		pthread_mutex_unlock(&needle->struct_dead->mutex);
	}
}

void	print(t_needle *needle, char *str, int flag)
{
	print_dead(needle, str, flag);
	print_logs(needle, str, flag);
}
