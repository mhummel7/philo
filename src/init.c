/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:06:00 by mhummel           #+#    #+#             */
/*   Updated: 2024/11/13 12:07:11 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!data->forks)
		ft_exit("Malloc failed to allocate memory", data);
	i = -1;
	while (++i < data->philo_num)
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			ft_exit("Mutex init failed", data);
	if (pthread_mutex_init(&data->lock, NULL) != 0)
		ft_exit("Mutex init failed", data);
	if (pthread_mutex_init(&data->write, NULL) != 0)
		ft_exit("Mutex init failed", data);
	return (0);
}

int	init_philosophers(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->philo_num);
	if (!data->philos)
		ft_exit("Malloc failed for philosophers", data);
	i = -1;
	while (++i < data->philo_num)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].eat_cont = 0;
		data->philos[i].status = 0;
		data->philos[i].eating = 0;
		data->philos[i].time_to_die = get_time() + data->death_time;
		if (pthread_mutex_init(&data->philos[i].lock, NULL) != 0)
			ft_exit("Mutex init failed", data);
		data->philos[i].r_fork = &data->forks[i];
		data->philos[i].l_fork = &data->forks[(i + 1) % data->philo_num];
	}
	return (0);
}

int	check_input_format(char **argv)
{
	int	i;

	if (argv[1][0] == '0' || argv[1][0] == '-')
	{
		printf("Error: Invalid input format\n");
		exit(1);
	}
	i = 2;
	while (i < 5)
	{
		if (argv[i][0] == '-')
		{
			printf("Error: Invalid input format\n");
			exit(1);
		}
		i++;
	}
	return (0);
}

int	check_must_eat(char **argv)
{
	if (argv[5][0] == '0')
		exit(0);
	if (argv[5][0] == '-')
	{
		printf("Error: Invalid input format\n");
		exit(1);
	}
	return (0);
}

int	init_input(int argc, char **argv, t_data *data)
{
	if (argc != 5 && argc != 6)
	{
		printf("Error: Wrong number of arguments\n");
		exit(1);
	}
	check_input_format(argv);
	data->philo_num = ft_atoi(argv[1]);
	if (data->philo_num > 200)
	{
		printf("Error: Too many philosophers\n");
		exit(1);
	}
	data->death_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
	{
		check_must_eat(argv);
		data->meals_nb = ft_atoi(argv[5]);
	}
	else
		data->meals_nb = -1;
	return (0);
}
