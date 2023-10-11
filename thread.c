/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyandriy <lyandriy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:58:23 by lyandriy          #+#    #+#             */
/*   Updated: 2023/10/11 18:17:25 by lyandriy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_sleep(t_needle *needle)
{
	the_logs(needle, "is sleeping", 4);
	ft_usleep(needle->tt_sleep, needle);
	return (1);
}

void	*start_routine(void *needle_original)
{
	t_needle	*needle;

	needle = (t_needle *) needle_original;
	while (1)
	{
		the_logs(needle, "is thinking", 1);
		if (!check_dead(needle))
			break ;
		if (!ft_lunch(needle))
			break ;
		if (!check_life(needle))
			break ;
		if (!check_dead(needle))
			break ;
		if (!ft_sleep(needle))
			break ;
		if (!check_life(needle))
			break ;
		if (!check_dead(needle))
			break ;
	}
	return (NULL);
}
