/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:15:09 by mhummel           #+#    #+#             */
/*   Updated: 2024/10/31 11:39:01 by mhummel          ###   ########.fr       */
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
				philosophers_routine, &data->philos[i]) != 0)
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

int	main(int argc, char **argv)
{
	t_data	data;

	data.philo_thread_id = NULL;
	data.philos = NULL;
	data.forks = NULL;
	data.dead = 0;
	data.finished = 0;
	init_input(argc, argv, &data);
	init_mutex(&data);
	init_philosophers(&data);
	create_threads(&data);
	join_threads(&data);
	cleanup(&data);
	return (0);
}
