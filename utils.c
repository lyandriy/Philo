/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyandriy <lyandriy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:52:29 by lyandriy          #+#    #+#             */
/*   Updated: 2023/10/18 17:48:53 by lyandriy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_time(uint64_t *timer)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	*timer = ((start.tv_sec * 1000) + (start.tv_usec / 1000));
}

int	check_return(int retur, t_philo *philo)
{
	if (retur)
	{
		ft_destroy(philo);
		printf("error\n");
		return (0);
	}
	return (1);
}

void	ft_usleep(uint64_t time, t_needle *needle)
{
	uint64_t	present_time;
	uint64_t	time_to_sleep;
	struct timeval	start;
	

	get_time(&present_time);
	time_to_sleep = present_time + time;
	while (time_to_sleep > present_time)
	{
		usleep(500);
		gettimeofday(&start, NULL);
		present_time = ((start.tv_sec * 1000) + (start.tv_usec / 1000));
		if (needle->tt_die < (present_time - needle->last_meal))
			check_life_2(needle, present_time);
	}
}

void	ft_destroy(t_philo *philo)
{
	int	i;

	i = 0;
	while (--philo->count_philo >= 0)
	{
		if (pthread_mutex_destroy(&philo->needle[philo->count_philo]->mutex))
			printf("error\n");
	}
	while (i < philo->num_ph)
	{
		free(philo->needle[i]);
		i++;
	}
	free(philo->needle);
}

void	print(t_needle *needle, char *str)
{
	uint64_t	timer;
	int			flag;

	flag = 0;
	get_time(&timer);
	timer = (timer - needle->birth_time);
	while (!flag)
	{
		pthread_mutex_lock(&needle->common_structure->mutex_print);
		if (!needle->common_structure->print_sign)
		{
			needle->common_structure->print_sign = 1;
			printf(DO, timer, (needle->my_number + 1), str);
			flag = 1;
			needle->common_structure->print_sign = 0;
		}
		pthread_mutex_unlock(&needle->common_structure->mutex_print);
		usleep (50);
	}
}
