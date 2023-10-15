/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lunch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyandriy <lyandriy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:16:58 by lyandriy          #+#    #+#             */
/*   Updated: 2023/10/15 19:58:01 by lyandriy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_left_fork(t_needle *needle, int *flag)
{
	while (*flag != needle->my_number)
	{
		pthread_mutex_lock(&needle->mutex);
		if (needle->waiting_threads == -1)
		{
			needle->waiting_threads = needle->my_number;
			*flag = needle->my_number;
		}
		pthread_mutex_unlock(&needle->mutex);
		check_life(needle);
		usleep(50);
	}
}

void	take_right_fork(t_needle *needle, int *flag2)
{
	while (*flag2 != needle->my_number)
	{
		if (needle->next_needle)
		{
			pthread_mutex_lock(&needle->next_needle[0]->mutex);
			if (needle->next_needle[0]->waiting_threads == -1)
			{
				needle->next_needle[0]->waiting_threads = needle->my_number;
				*flag2 = needle->my_number;
			}
			pthread_mutex_unlock(&needle->next_needle[0]->mutex);
		}
		check_life(needle);
		usleep(50);
	}
}

void	lunch(t_needle *needle)
{
	the_logs(needle, "has taken a fork", 2);
	the_logs(needle, "is eating", 3);
	get_time(&needle->last_meal);
	ft_usleep(needle->tt_eat, needle);
}

void	free_fork(t_needle *needle)
{
	pthread_mutex_lock(&needle->mutex);
	needle->waiting_threads = -1;
	pthread_mutex_unlock(&needle->mutex);
	pthread_mutex_lock(&needle->next_needle[0]->mutex);
	needle->next_needle[0]->waiting_threads = -1;
	pthread_mutex_unlock(&needle->next_needle[0]->mutex);
}


void	ft_lunch(t_needle *needle)
{
	int	flag;
	int	flag2;

	flag = -1;
	flag2 = -1;
	/*if (needle->must_eat)
	{
		if (needle->number_of_meals >= needle->must_eat)
			return (0);
	}*/
	take_left_fork(needle, &flag);
	the_logs(needle, "has taken a fork", 2);
	take_right_fork(needle, &flag2);
	lunch(needle);
	free_fork(needle);
	needle->number_of_meals++;
}
