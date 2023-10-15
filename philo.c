/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyandriy <lyandriy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 18:49:44 by lyandriy          #+#    #+#             */
/*   Updated: 2023/10/15 20:10:02 by lyandriy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	make_mutex(t_philo *philo)
{
	int	retur;

	fill_needle(philo);
	retur = pthread_mutex_init(&philo->needle[philo->count_philo]->mutex, NULL);
	if (!check_return(retur, philo))
		return (0);
	philo->count_philo++;
	return (1);
}

int	make_thread(t_philo *philo)
{
	int	retur;

	philo->needle[philo->count_philo]->birth_time = philo->birth_time;
	retur = pthread_create(&philo->needle[philo->count_philo]->thread,
			NULL, start_routine, (void *)philo->needle[philo->count_philo]);
	if (!check_return(retur, philo))
		return (0);
	philo->count_philo++;
	return (1);
}

int	make_thread_join(pthread_t *thread, t_philo *philo)
{
	int	retur;

	retur = pthread_join(*thread, NULL);
	if (!check_return(retur, philo))
		return (0);
	return (1);
}
void	check_thred(t_philo *philo)
{
	int	flag2 = 0;
	while (1)
	{
		pthread_mutex_lock(&philo->common_structure.mutex);
		if(philo->common_structure.death_sign == 1)
		{
			while(!flag2)
			{
				pthread_mutex_lock(&philo->common_structure.mutex_print);
				if (philo->common_structure.print_sign == 2)
					flag2 = 2;
				if (philo->common_structure.print_sign == -1)
				{
					philo->common_structure.print_sign = 2;
					flag2 = 1;
				}
				pthread_mutex_unlock(&philo->common_structure.mutex_print);
			}
			if (flag2 == 1)
				printf(DEAD, philo->common_structure.time_die, (philo->common_structure.numb_philo + 1), "died");
			break ;
		}
		pthread_mutex_unlock(&philo->common_structure.mutex);
	}
}

int	make_philos(t_philo *philo)
{
	int	i;

	i = 0;
	while (philo->count_philo != philo->num_ph)
	{
		if (!make_mutex(philo))
			return (0);
	}
	philo->count_philo = 0;
	while (philo->count_philo != philo->num_ph)
	{
		get_time(&philo->birth_time);
		if (!make_thread(philo))
			return (0);
	}
	pthread_mutex_lock(&philo->common_structure.mutex);
	philo->common_structure.thred_sign = 1;
	pthread_mutex_unlock(&philo->common_structure.mutex);
	check_thred(philo);
	while (i != philo->num_ph)
	{
		if (!make_thread_join(&philo->needle[i++]->thread, philo))
			return (0);
	}
	return (1);
}

void	ft_philo(t_philo *philo)
{
	if (init(philo))
	{
		if (make_philos(philo))
			ft_destroy(philo);
	}
}
