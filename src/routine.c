/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:37:48 by mhummel           #+#    #+#             */
/*   Updated: 2024/10/31 13:40:13 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philosopher_eat(t_philo *philo)
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

static int	check_if_finished(t_philo *philo)
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

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->philo_num == 1)
	{
		print_status(philo, "has taken a fork");
		sleep_time(philo->data->death_time);
		return (NULL);
	}
	if (philo->id % 2)
		usleep(1000);
	while (!philo->data->dead)
	{
		philosopher_eat(philo);
		if (check_if_finished(philo))
			return (NULL);
		print_status(philo, "is sleeping");
		sleep_time(philo->data->sleep_time);
		print_status(philo, "is thinking");
	}
	return (NULL);
}
