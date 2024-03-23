/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lunch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyandriy <lyandriy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:16:58 by lyandriy          #+#    #+#             */
/*   Updated: 2023/10/26 19:18:15 by lyandriy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_right_fork(t_needle *needle)
{
	int	flag;

	flag = 0;
	if (needle->number_of_meals && !(needle->my_number % 2)
		&& (needle->num_ph % 2))
		usleep (100);
	while (!flag)
	{
		pthread_mutex_lock(&needle->mutex);
		if (!needle->waiting_threads)
		{
			needle->waiting_threads = 1;
			flag = 1;
		}
		pthread_mutex_unlock(&needle->mutex);
		if (!check_life(needle))
			flag = 1;
		usleep(100);
	}
	print(needle, "has taken a fork");
}

void	take_left_fork(t_needle *needle)
{
	int	flag;

	flag = 0;
	if (needle->number_of_meals && !(needle->my_number % 2)
		&& (needle->num_ph % 2))
		usleep (100);
	while (!flag)
	{
		pthread_mutex_lock(&needle->next_needle[0]->mutex);
		if (!needle->next_needle[0]->waiting_threads)
		{
			needle->next_needle[0]->waiting_threads = 1;
			flag = 1;
		}
		pthread_mutex_unlock(&needle->next_needle[0]->mutex);
		if (!check_life(needle))
			flag = 1;
		usleep(100);
	}
	print(needle, "has taken a fork");
}

void	lunch(t_needle *needle)
{
	print(needle, "is eating");
	get_time(&needle->last_meal);
	ft_usleep(needle->tt_eat, needle);
}

void	free_fork(t_needle *needle)
{
	pthread_mutex_lock(&needle->mutex);
	needle->waiting_threads = 0;
	pthread_mutex_unlock(&needle->mutex);
	pthread_mutex_lock(&needle->next_needle[0]->mutex);
	needle->next_needle[0]->waiting_threads = 0;
	pthread_mutex_unlock(&needle->next_needle[0]->mutex);
}

void	ft_lunch(t_needle *needle)
{
	if (needle->my_number % 2)
	{
		take_left_fork(needle);
		take_right_fork(needle);
	}
	else
	{
		take_right_fork(needle);
		take_left_fork(needle);
	}
	lunch(needle);
	free_fork(needle);
	needle->number_of_meals++;
}
