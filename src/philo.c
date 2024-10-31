/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:15:09 by mhummel           #+#    #+#             */
/*   Updated: 2024/10/31 13:13:51 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philosopher_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->l_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->time_to_die = get_time() + philo->data->death_time;
	print_status(philo, "is eating");
	philo->eat_cont++;
	sleep_time(philo->data->eat_time);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

int	check_if_finished(t_philo *philo)
{
	if (philo->data->meals_nb != -1 && philo->eat_cont >= philo->data->meals_nb)
	{
		pthread_mutex_lock(&philo->data->lock);
		philo->data->finished++;
		if (philo->data->finished >= philo->data->philo_num)
		{
			pthread_mutex_unlock(&philo->data->lock);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->lock);
		return (0);
	}
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
