/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dravaono <dravaono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:46:40 by dravaono          #+#    #+#             */
/*   Updated: 2024/06/27 19:51:02 by dravaono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*check_die(void *ptr)
{
	t_data	*data;

	data = (t_data *)ptr;
	while (1)
	{
		if (data->nb_eat > 0)
		{
			if (check_onedie(data) == 1 || check_eat(data) == 1)
				break ;
		}
		else if (check_onedie(data) == 1)
			break ;
	}
	return (0);
}

int	check_eat(t_data *data)
{
	data->j = 0;
	data->count = 0;
	while (data->j < data->num_philo)
	{
		pthread_mutex_lock(&data->fulltruetwo);
		if (data->philo[data->j].full == true)
		{
			pthread_mutex_unlock(&data->fulltruetwo);
			data->j++;
			data->count++;
		}
		else
		{
			pthread_mutex_unlock(&data->fulltruetwo);
			return (0);
		}
	}
	if (data->count == data->num_philo)
	{
		fulltrue(data);
		return (1);
	}
	else
		return (0);
}

int	check_onedie(t_data *data)
{
	int	time;
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_lock(&data->time_eatnow);
		time = get_time() - data->philo[i].last_time_to_eat;
		pthread_mutex_unlock(&data->time_eatnow);
		if (time > data->time_to_die)
		{
			pthread_mutex_lock(&data->istrue);
			data->die = true;
			pthread_mutex_unlock(&data->istrue);
			return (1);
		}
		i++;
	}
	return (0);
}

void	fulltrue(t_data *data)
{
	pthread_mutex_lock(&data->istrue);
	data->full = true;
	pthread_mutex_unlock(&data->istrue);
}
