/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyandriy <lyandriy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:52:29 by lyandriy          #+#    #+#             */
/*   Updated: 2023/10/15 19:58:50 by lyandriy         ###   ########.fr       */
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

void	the_logs(t_needle *needle, char *str, int flag)
{
	//if (check_dead(needle))
		print(needle, str, flag);
}

void	ft_usleep(uint64_t time, t_needle *needle)
{
	uint64_t	present_time;
	uint64_t	time_to_sleep;
	uint64_t	time_to_sleep_st;

	get_time(&present_time);
	time_to_sleep = present_time + time;
	time_to_sleep_st = present_time;
	while (time_to_sleep > present_time)
	{
		usleep(40);
		get_time(&present_time);
		check_life(needle);
	}
	//printf("%lld\n", (present_time - time_to_sleep_st));
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
