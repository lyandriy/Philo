/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyandriy <lyandriy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:52:29 by lyandriy          #+#    #+#             */
/*   Updated: 2023/10/27 20:10:33 by lyandriy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_return(int retur)
{
	if (retur)
	{
		printf("error\n");
		return (0);
	}
	return (1);
}

void	ft_destroy(t_philo *philo)
{
	int	i;

	i = 0;
	if (pthread_mutex_destroy(&philo->common_structure.mutex))
		printf("error\n");
	if (pthread_mutex_destroy(&philo->common_structure.mutex_print))
		printf("error\n");
	if (pthread_mutex_destroy(&philo->common_structure.eat))
		printf("error\n");
	while (i < philo->num_ph)
		pthread_mutex_destroy(&philo->needle[i++]->mutex);
	i = 0;
	if (philo->needle)
	{
		while (i < philo->count_philo)
		{
			if (philo->needle[i])
				free(philo->needle[i]);
			i++;
		}
		free(philo->needle);
	}
}

void	check_thred(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->common_structure.mutex);
		if (philo->common_structure.death_sign == 1)
		{
			pthread_mutex_lock(&philo->common_structure.mutex_print);
			if (!philo->common_structure.print_sign)
				philo->common_structure.print_sign = 1;
			printf(DO, philo->common_structure.time_die,
				(philo->common_structure.numb_philo + 1), "died");
			pthread_mutex_unlock(&philo->common_structure.mutex_print);
			pthread_mutex_unlock(&philo->common_structure.mutex);
			break ;
		}
		pthread_mutex_lock(&philo->common_structure.eat);
		if (philo->common_structure.philosopher_eat == philo->num_ph)
		{
			pthread_mutex_unlock(&philo->common_structure.eat);
			pthread_mutex_unlock(&philo->common_structure.mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->common_structure.eat);
		pthread_mutex_unlock(&philo->common_structure.mutex);
	}
}

void	can_start(t_philo *philo)
{
	pthread_mutex_lock(&philo->common_structure.mutex);
	philo->common_structure.thred_sign = 1;
	pthread_mutex_unlock(&philo->common_structure.mutex);
}
