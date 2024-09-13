/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dravaono <dravaono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 20:09:39 by dravaono          #+#    #+#             */
/*   Updated: 2024/06/27 19:54:56 by dravaono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->num_philo);
	while (i < data->num_philo)
	{
		data->philo[i].philo_number = i + 1;
		data->philo[i].fork_right = (i + 1) % data->num_philo;
		data->philo[i].fork_left = i;
		data->philo[i].data = data;
		data->philo[i].has_eaten = 0;
		data->philo[i].last_time_to_eat = get_time();
		data->philo[i].ubereats = 0;
		data->philo[i].full = false;
		i++;
	}
	data->start = get_time();
}

void	all_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philo)
	{
		pthread_mutex_init(&data->fork[i], NULL);
	}
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->check_die, NULL);
	pthread_mutex_init(&data->eat_rout, NULL);
	pthread_mutex_init(&data->time_eatnow, NULL);
	pthread_mutex_init(&data->time_eatcheckdie, NULL);
	pthread_mutex_init(&data->istrue, NULL);
	pthread_mutex_init(&data->ubereats, NULL);
	pthread_mutex_init(&data->isfull, NULL);
	pthread_mutex_init(&data->fulltrue, NULL);
	pthread_mutex_init(&data->fulltruetwo, NULL);
}

void	util(char **str, t_data *data)
{
	int	i;

	data->num_philo = ft_atoi(str[1]);
	data->time_to_die = ft_atoi(str[2]);
	data->time_to_eat = ft_atoi(str[3]);
	data->time_to_sleep = ft_atoi(str[4]);
	data->nb_eat = 0;
	if (str[5])
		data->nb_eat = ft_atoi(str[5]);
	data->die = false;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	init_philo(data);
	all_mutex(data);
	i = -1;
	while (++i < data->num_philo)
		pthread_create(&data->philo[i].thread, NULL, routine, &data->philo[i]);
	pthread_create(&data->superviseurdie, NULL, check_die, data);
}
