/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyandriy <lyandriy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:19:57 by lyandriy          #+#    #+#             */
/*   Updated: 2023/10/20 17:47:05 by lyandriy         ###   ########.fr       */
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

int	make_join(pthread_t *thread, t_philo *philo)
{
	int	retur;

	retur = pthread_join(*thread, NULL);
	if (!check_return(retur, philo))
		return (0);
	return (1);
}

int	make_philos(t_philo *philo)
{
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
	philo->count_philo = 0;
	while (philo->count_philo != philo->num_ph)
	{
		if (!make_join(&philo->needle[philo->count_philo++]->thread, philo))
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
