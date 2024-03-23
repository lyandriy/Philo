/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyandriy <lyandriy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:19:57 by lyandriy          #+#    #+#             */
/*   Updated: 2023/10/27 20:34:12 by lyandriy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	make_mutex(t_philo *philo)
{
	int	retur;

	fill_needle(philo);
	retur = pthread_mutex_init(&philo->needle[philo->count_philo]->mutex, NULL);
	if (!check_return(retur))
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
	if (!check_return(retur))
		return (0);
	philo->count_philo++;
	return (1);
}

int	make_join(pthread_t *thread)
{
	int	retur;

	retur = pthread_join(*thread, NULL);
	if (!check_return(retur))
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
	while (philo->count_philo != philo->num_ph)
	{
		get_time(&philo->birth_time);
		if (!make_thread(philo))
			return (0);
		if (philo->count_philo == philo->num_ph)
			can_start(philo);
	}
	check_thred(philo);
	while (i != philo->num_ph)
	{
		if (!make_join(&philo->needle[i++]->thread))
			return (0);
	}
	return (1);
}

void	ft_philo(t_philo *philo)
{
	if (init(philo))
		make_philos(philo);
	ft_destroy(philo);
}
