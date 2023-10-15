/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyandriy <lyandriy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:37:06 by lyandriy          #+#    #+#             */
/*   Updated: 2023/10/15 18:05:11 by lyandriy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_dead(t_needle *needle, char *str, int flag)
{
	uint64_t	timer;

	if (!flag)
	{
		int	flag2 = 0;
		while(!flag2)
		{
			pthread_mutex_lock(&needle->common_structure->mutex_print);
			if (needle->common_structure->print_sign == 2)
				flag2 = 2;
			if (needle->common_structure->print_sign == -1)
			{
				needle->common_structure->print_sign = 2;
				flag2 = 1;
			}
			pthread_mutex_unlock(&needle->common_structure->mutex_print);
		}
		if (flag2 == 1)
		{
			get_time(&timer);
			timer = (timer - needle->birth_time);
			pthread_mutex_lock(&needle->mutex);
			printf(DEAD, timer, (needle->my_number + 1), str);
			pthread_mutex_unlock(&needle->mutex);
		}
	}
}

void	print_logs(t_needle *needle, char *str, int flag)
{
	uint64_t	timer;

	if (flag)
	{
		int	flag2 = 0;
		while(!flag2)
		{
			pthread_mutex_lock(&needle->common_structure->mutex_print);
			if (needle->common_structure->print_sign == -1)
			{
				needle->common_structure->print_sign = 0;
				flag2 = 1;
			}
			if (needle->common_structure->print_sign == 2)
				flag2 = 2;
			pthread_mutex_unlock(&needle->common_structure->mutex_print);
		}
		if (flag2 == 1)
		{
			get_time(&timer);
			timer = (timer - needle->birth_time);
			pthread_mutex_lock(&needle->mutex);
			if (flag == 1)
				printf(THINK, timer, (needle->my_number + 1), str);
			if (flag == 2)
				printf(FORK, timer, (needle->my_number + 1), str);
			if (flag == 3)
				printf(EATING, timer, (needle->my_number + 1), str);
			if (flag == 4)
				printf(SLEEP, timer, (needle->my_number + 1), str);
			pthread_mutex_unlock(&needle->mutex);
			flag2 = 0;
		}
		while(!flag2)
		{
			pthread_mutex_lock(&needle->common_structure->mutex_print);
			if (needle->common_structure->print_sign == 0)
			{
				needle->common_structure->print_sign = -1;
				flag2 = 1;
			}
			pthread_mutex_unlock(&needle->common_structure->mutex_print);
		}
	}
}

void	print(t_needle *needle, char *str, int flag)
{
	print_dead(needle, str, flag);
	print_logs(needle, str, flag);
}
