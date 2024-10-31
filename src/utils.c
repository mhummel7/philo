/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:32:44 by mhummel           #+#    #+#             */
/*   Updated: 2024/10/31 12:57:00 by mhummel          ###   ########.fr       */
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

void	ft_exit(char *str, t_data *data)
{
	int	i;

	printf("Error: %s\n", str);
	if (data)
	{
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
	exit(1);
}

int	ft_atoi(const char *str, t_data *data)
{
	unsigned long	res;
	int				i;

	i = 0;
	res = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == '\v')
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		if (res > INT_MAX)
			ft_exit("Number too large", data);
		i++;
	}
	if (str[i] != '\0')
		ft_exit("Invalid number format", data);
	return ((int)res);
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

uint64_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	sleep_time(uint64_t time)
{
	uint64_t	start;
	uint64_t	current;

	start = get_time();
	while (1)
	{
		current = get_time();
		if (current - start >= time)
			break ;
		usleep(100);
	}
}
