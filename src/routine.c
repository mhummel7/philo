/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:37:48 by mhummel           #+#    #+#             */
/*   Updated: 2024/11/12 11:02:41 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		print_status(philo, "has taken a fork");
	}
}

static void	philosopher_eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->time_to_die = get_time() + philo->data->death_time;
	print_status(philo, "is eating");
	philo->eat_cont++;
	pthread_mutex_unlock(&philo->lock);
	ft_sleep(philo->data->eat_time, philo->data);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

static int	check_if_finished(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock);
	if (philo->data->meals_nb != -1 && philo->eat_cont >= philo->data->meals_nb)
	{
		philo->data->finished++;
		if (philo->data->finished >= philo->data->philo_num)
		{
			philo->data->dead = 1;
			pthread_mutex_unlock(&philo->data->lock);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->data->lock);
	return (0);
}

static int	handle_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock);
	if (philo->data->dead)
		return (pthread_mutex_unlock(&philo->data->lock), 1);
	pthread_mutex_unlock(&philo->data->lock);
	philosopher_eat(philo);
	if (check_if_finished(philo))
		return (1);
	print_status(philo, "is sleeping");
	ft_sleep(philo->data->sleep_time, philo->data);
	pthread_mutex_lock(&philo->data->lock);
	if (philo->data->dead)
		return (pthread_mutex_unlock(&philo->data->lock), 1);
	pthread_mutex_unlock(&philo->data->lock);
	print_status(philo, "is thinking");
	return (0);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->lock);
	philo->time_to_die = get_time() + philo->data->death_time;
	pthread_mutex_unlock(&philo->lock);
	if (philo->data->philo_num == 1)
	{
		print_status(philo, "has taken a fork");
		ft_sleep(philo->data->death_time, philo->data);
		return (NULL);
	}
	if (philo->id % 2)
		usleep(100);
	while (!handle_routine(philo))
		;
	return (NULL);
}
