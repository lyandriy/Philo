/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyandriy <lyandriy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 18:16:59 by lyandriy          #+#    #+#             */
/*   Updated: 2023/10/08 19:01:52 by lyandriy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	seeleaks()
{
	system("leaks -q philo");
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	//atexit(&seeleaks);
	if (assign_value(&philo, argv, argc))
		ft_philo(&philo);
}
