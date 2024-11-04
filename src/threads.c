/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:51:53 by mhummel           #+#    #+#             */
/*   Updated: 2024/11/04 12:30:24 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_data *data)
{
	int	i;

	data->philo_thread_id = malloc(sizeof(pthread_t) * data->philo_num);
	if (!data->philo_thread_id)
		ft_exit("Malloc failed for thread IDs", data);
	data->start_time = get_time();
	i = -1;
	while (++i < data->philo_num)
	{
		pthread_mutex_lock(&data->philos[i].lock);
		data->philos[i].time_to_die = get_time() + data->death_time;
		pthread_mutex_unlock(&data->philos[i].lock);
		if (pthread_create(&data->philo_thread_id[i], NULL, philosopher_routine,
				&data->philos[i]) != 0)
			ft_exit("Thread creation failed", data);
		usleep(100);
	}
	return (0);
}

int	join_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
		if (pthread_join(data->philo_thread_id[i], NULL) != 0)
			ft_exit("Thread join failed", data);
	return (0);
}
