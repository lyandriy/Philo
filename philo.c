/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyandriy <lyandriy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 18:49:44 by lyandriy          #+#    #+#             */
/*   Updated: 2023/10/11 18:55:45 by lyandriy         ###   ########.fr       */
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
	get_time(&philo->birth_time);
	while (philo->count_philo != philo->num_ph)
	{
		if (!make_thread(philo))
			return (0);
	}
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
