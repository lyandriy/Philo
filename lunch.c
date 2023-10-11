/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lunch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyandriy <lyandriy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:16:58 by lyandriy          #+#    #+#             */
/*   Updated: 2023/10/11 18:30:46 by lyandriy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	utils_lunch(t_needle *needle, int *flag)
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
		if (!check_life(needle))
			return (0);
	}
	return (1);
}

int	utils_lunch2(t_needle *needle, int *flag2)
{
	while (*flag2 != needle->my_number)
	{
		if (needle->next_needle[0])
		{
			pthread_mutex_lock(&needle->next_needle[0]->mutex);
			if (needle->next_needle[0]->waiting_threads == -1)
			{
				needle->next_needle[0]->waiting_threads = needle->my_number;
				*flag2 = needle->my_number;
			}
			pthread_mutex_unlock(&needle->next_needle[0]->mutex);
		}
		if (!check_life(needle))
			return (0);
	}
	return (1);
}

int	utils_lunch3(t_needle *needle, int *flag, int *flag2)
{
	if (*flag == needle->my_number)
	{
		if (!pthread_mutex_lock(&needle->mutex))
		{
			if (needle->waiting_threads == needle->my_number)
				needle->waiting_threads = -1;
			pthread_mutex_unlock(&needle->mutex);
		}
		if (!check_life(needle))
			return (0);
	}
	if (*flag2 == needle->my_number)
	{
		if (!pthread_mutex_lock(&needle->next_needle[0]->mutex))
		{
			if (needle->next_needle[0]->waiting_threads == needle->my_number)
				needle->next_needle[0]->waiting_threads = -1;
			pthread_mutex_unlock(&needle->next_needle[0]->mutex);
		}
		if (!check_life(needle))
			return (0);
	}
	return (1);
}

void	utils_lunch4(t_needle *needle)
{
	the_logs(needle, "has taken a right fork", 2);
	get_time(&needle->last_meal);
	the_logs(needle, "is eating", 3);
	ft_usleep(needle->tt_eat, needle);
}

int	ft_lunch(t_needle *needle)
{
	int	flag;
	int	flag2;

	flag = -1;
	flag2 = -1;
	if (needle->must_eat)
	{
		if (needle->number_of_meals >= needle->must_eat)
			return (0);
	}
	if (needle->number_of_meals == 0 && needle->my_number % 2)
		usleep(90);
	if (!utils_lunch(needle, &flag))
		return (0);
	the_logs(needle, "has taken a left fork", 2);
	if (!utils_lunch2(needle, &flag2))
		return (0);
	utils_lunch4(needle);
	if (!check_life(needle))
		return (0);
	if (!utils_lunch3(needle, &flag, &flag2))
		return (0);
	needle->number_of_meals++;
	return (1);
}
