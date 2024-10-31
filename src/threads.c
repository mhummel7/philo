/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:51:53 by mhummel           #+#    #+#             */
/*   Updated: 2024/10/31 13:02:46 by mhummel          ###   ########.fr       */
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
		data->philos[i].time_to_die = data->start_time + data->death_time;
		if (pthread_create(&data->philo_thread_id[i], NULL,
				philosopher_routine, &data->philos[i]) != 0)
			ft_exit("Thread creation failed", data);
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
