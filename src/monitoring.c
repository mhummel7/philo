/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:43:15 by mhummel           #+#    #+#             */
/*   Updated: 2024/11/04 12:27:06 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_death(t_data *data)
{
	int			i;
	uint64_t	current_time;
	uint64_t	last_eat_time;

	while (!data->finished && !data->dead)
	{
		i = -1;
		while (++i < data->philo_num)
		{
			pthread_mutex_lock(&data->philos[i].lock);
			current_time = get_time();
			last_eat_time = data->philos[i].time_to_die - data->death_time;
			if (!data->philos[i].eating
				&& (current_time - last_eat_time) >= data->death_time)
			{
				print_status(&data->philos[i], "died");
				pthread_mutex_lock(&data->lock);
				data->dead = 1;
				pthread_mutex_unlock(&data->lock);
				pthread_mutex_unlock(&data->philos[i].lock);
				return ;
			}
			pthread_mutex_unlock(&data->philos[i].lock);
		}
		usleep(100);
	}
}

void	print_status(t_philo *philo, char *msg)
{
	uint64_t	time;

	pthread_mutex_lock(&philo->data->write);
	if (!philo->data->dead)
	{
		time = get_time() - philo->data->start_time;
		printf("%llu %d %s\n", time, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->write);
}
