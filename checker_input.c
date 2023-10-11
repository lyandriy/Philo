/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyandriy <lyandriy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:20:39 by lyandriy          #+#    #+#             */
/*   Updated: 2023/10/11 18:50:38 by lyandriy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	unsigned int	num;
	int				i;
	int				neg;

	i = 0;
	neg = 1;
	num = 0;
	while (str[i] == 32 || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		num = (str[i] - 48) + (num * 10);
		i++;
		if (num > 2147483647 && neg == 1)
			return (-1);
		else if (num > 2147483648 && neg == -1)
			return (-1);
	}
	return (num * neg);
}

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

int	check_input(char **argv)
{
	int	count;
	int	count_char;

	count = 1;
	while (argv[count])
	{
		count_char = 0;
		while (argv[count][count_char])
		{
			if (!ft_isdigit(argv[count][count_char]))
				return (0);
			count_char++;
		}
		count++;
	}
	return (1);
}

int	check_size(t_philo *philo)
{
	if ((philo->num_ph == -1) || (philo->tt_die == -1) || (philo->tt_eat == -1)
		|| (philo->tt_sleep == -1) || (philo->must_eat == -1))
	{
		printf("Invalid input\n");
		return (0);
	}
	return (1);
}

int	assign_value(t_philo *philo, char **argv, int argc)
{
	if (argc < 5 || argc > 6)
		printf("Invalid input\n");
	else if (!check_input(argv))
		printf("Invalid input\n");
	else if (argc == 6 && ft_atoi(argv[5]) == 0)
		return (0);
	else
	{
		philo->num_ph = ft_atoi(argv[1]);
		philo->tt_die = (uint64_t)ft_atoi(argv[2]);
		philo->tt_eat = (uint64_t)ft_atoi(argv[3]);
		philo->tt_sleep = (uint64_t)ft_atoi(argv[4]);
		philo->must_eat = 0;
		if (argv[5])
			philo->must_eat = ft_atoi(argv[5]);
		if (check_size(philo))
			return (1);
	}
	return (0);
}
