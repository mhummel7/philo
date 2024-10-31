/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:43:15 by mhummel           #+#    #+#             */
/*   Updated: 2024/10/31 13:47:41 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_death(t_data *data)
{
	int			i;
	uint64_t	current_time;

	while (!data->finished && !data->dead)
	{
		i = -1;
		while (++i < data->philo_num)
		{
			pthread_mutex_lock(&data->philos[i].lock);
			current_time = get_time();
			if (!data->philos[i].eating
				&& current_time > data->philos[i].time_to_die)
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
