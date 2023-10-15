/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prueba.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyandriy <lyandriy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:13:07 by lyandriy          #+#    #+#             */
/*   Updated: 2023/10/15 16:15:50 by lyandriy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

uint64_t	get_timer(void)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	return ((start.tv_sec * 1000) + (start.tv_usec / 1000));
}

void	ft_usleep(void)
{
	uint64_t time = 200;
	uint64_t	present_time = get_timer();
	while ((get_timer() - present_time) < time)
		usleep (40);
	uint64_t	time_to_sleep2 = get_timer();
	printf("Salgo con %lld milisegundos (time: %lld).\n", (time_to_sleep2 - present_time), time);
}

int main(void)
{
	int i = 0;
	while(i != 200)
	{
		i++;
		ft_usleep();
	}
}