/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:48:15 by mhummel           #+#    #+#             */
/*   Updated: 2024/11/04 13:25:00 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

struct	s_data;

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		thread_id;
	int				id;
	int				eat_cont;
	int				status;
	int				eating;
	uint64_t		time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}					t_philo;

typedef struct s_data
{
	pthread_t		*philo_thread_id;
	int				philo_num;
	int				meals_nb;
	int				dead;
	int				finished;
	t_philo			*philos;
	u_int64_t		death_time;
	u_int64_t		eat_time;
	u_int64_t		sleep_time;
	u_int64_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}					t_data;

//
// utils.c
//
void		ft_exit(char *str, t_data *data);
int			ft_atoi(const char *str, t_data *data);
void		sleep_time(uint64_t time);
uint64_t	get_time(void);

//
// input.c
//
int			init_mutex(t_data *data);
int			init_philosophers(t_data *data);
int			init_input(int argc, char **argv, t_data *data);

//
// routine.c
//
void		*philosopher_routine(void *arg);

//
// monitoring.c
//
void		check_death(t_data *data);
void		print_status(t_philo *philo, char *msg);

//
// threads.c
//
int			create_threads(t_data *data);
int			join_threads(t_data *data);

//
// philo.c
//
void		cleanup(t_data *data);

#endif