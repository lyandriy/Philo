/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyandriy <lyandriy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:51:07 by lyandriy          #+#    #+#             */
/*   Updated: 2023/10/11 18:38:40 by lyandriy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fill_needle(t_philo *philo)
{
	if (philo->needle[philo->count_philo])
	{
		philo->needle[philo->count_philo]->number_of_meals = 0;
		philo->needle[philo->count_philo]->last_meal = 0;
		philo->needle[philo->count_philo]->num_ph = philo->num_ph;
		philo->needle[philo->count_philo]->waiting_threads = -1;
		philo->needle[philo->count_philo]->tt_die = philo->tt_die;
		philo->needle[philo->count_philo]->tt_eat = philo->tt_eat;
		philo->needle[philo->count_philo]->tt_sleep = philo->tt_sleep;
		philo->needle[philo->count_philo]->must_eat = philo->must_eat;
		philo->needle[philo->count_philo]->my_number = philo->count_philo;
		if (philo->count_philo == (philo->num_ph - 1))
			philo->needle[philo->count_philo]->next_needle = &philo->needle[0];
		else if (philo->num_ph == 1)
			philo->needle[philo->count_philo]->next_needle = NULL;
		else
			philo->needle[philo->count_philo]->next_needle
				= &philo->needle[philo->count_philo + 1];
		philo->needle[philo->count_philo]->struct_dead = &philo->struct_dead;
	}
}

int	init(t_philo *philo)
{
	int	retur;
	int	i;

	i = 0;
	retur = pthread_mutex_init(&philo->struct_dead.mutex, NULL);
	check_return(retur, philo);
	philo->count_philo = 0;
	philo->struct_dead.print_sign = -1;
	philo->struct_dead.death_sign = 0;
	philo->needle = (t_needle **)malloc (sizeof(t_needle *) * (philo->num_ph));
	if (!philo->needle)
		return (0);
	while (i < philo->num_ph)
	{
		philo->needle[i] = (t_needle *)malloc (sizeof(t_needle));
		if (!philo->needle[i])
			return (0);
		i++;
	}
	return (1);
}
