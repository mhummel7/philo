/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:32:44 by mhummel           #+#    #+#             */
/*   Updated: 2024/11/13 12:09:08 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	ft_atoi(const char *str)
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
		{
			printf("Error: Number too large\n");
			exit(1);
		}
		i++;
	}
	if (str[i] != '\0')
		(printf("Error: Invalid number format\n"), exit(1));
	return ((int)res);
}

uint64_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_sleep(uint64_t time, t_data *data)
{
	uint64_t	start;

	start = get_time();
	while (get_time() - start < time)
	{
		pthread_mutex_lock(&data->lock);
		if (data->dead)
		{
			pthread_mutex_unlock(&data->lock);
			return ;
		}
		pthread_mutex_unlock(&data->lock);
		usleep(500);
	}
}
