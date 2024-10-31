/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:15:09 by mhummel           #+#    #+#             */
/*   Updated: 2024/10/31 13:41:52 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	cleanup(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = -1;
		while (++i < data->philo_num)
			pthread_mutex_destroy(&data->forks[i]);
		free(data->forks);
	}
	if (data->philos)
	{
		i = -1;
		while (++i < data->philo_num)
			pthread_mutex_destroy(&data->philos[i].lock);
		free(data->philos);
	}
	if (data->philo_thread_id)
		free(data->philo_thread_id);
	pthread_mutex_destroy(&data->lock);
	pthread_mutex_destroy(&data->write);
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
