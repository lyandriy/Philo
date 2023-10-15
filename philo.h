/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyandriy <lyandriy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 18:17:04 by lyandriy          #+#    #+#             */
/*   Updated: 2023/10/15 19:58:10 by lyandriy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

/*# define DEAD	"\x1b[31m %llu %d %s \x1b[0m \n"
# define THINK	"\x1b[34m %llu %d %s \x1b[0m \n"
# define FORK	"\x1b[35m %llu %d %s \x1b[0m \n"
# define EATING	"\x1b[33m %llu %d %s \x1b[0m \n"
# define SLEEP	"\x1b[32m %llu %d %s \x1b[0m \n"*/

# define DEAD	"%llu %d %s\n"
# define THINK	"%llu %d %s\n"
# define FORK	"%llu %d %s\n"
# define EATING	"%llu %d %s\n"
# define SLEEP	"%llu %d %s\n"

typedef pthread_mutex_t	t_mutex;

typedef struct s_dead
{
	int		thred_sign;
	int		print_sign;
	int		death_sign;
	uint64_t	time_die;
	int			numb_philo;
	t_mutex	mutex_print;
	t_mutex	mutex;
}	t_dead;

typedef struct s_needle
{
	int				num_ph;
	uint64_t		tt_die;
	uint64_t		tt_eat;
	uint64_t		tt_sleep;
	int				number_of_meals;
	int				must_eat;
	int				my_number;
	int				waiting_threads;
	t_dead			*common_structure;
	uint64_t		last_meal;
	uint64_t		birth_time;
	pthread_t		thread;
	t_mutex			mutex;
	struct s_needle	**next_needle;
}	t_needle;

typedef struct s_philo
{
	int			num_ph;
	int			tt_die;
	int			tt_eat;
	int			tt_sleep;
	int			must_eat;
	int			count_philo;
	t_dead		common_structure;
	uint64_t	birth_time;
	t_needle	**needle;
}	t_philo;

void	ft_philo(t_philo *philo);
int		assign_value(t_philo *philo, char **argv, int argc);
int		init(t_philo *philo);
int		check_return(int retur, t_philo *philo);
void	fill_needle(t_philo *philo);
void	get_time(uint64_t *timer);
void	*start_routine(void *needle_original);
int		check_dead(t_needle *needle);
void	check_life(t_needle *needle);
void	the_logs(t_needle *needle, char *str, int flag);
void	ft_usleep(uint64_t time, t_needle *needle);
void	ft_destroy(t_philo *philo);
void	print(t_needle *needle, char *str, int flag);
void	ft_lunch(t_needle *needle);
void	free_fork(t_needle *needle);

#endif