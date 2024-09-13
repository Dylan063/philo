/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dravaono <dravaono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 20:04:46 by dravaono          #+#    #+#             */
/*   Updated: 2024/06/27 19:56:07 by dravaono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->philo_number % 2 == 0)
		usleep(2500);
	if (philo->data->num_philo == 1)
		onephilo(philo->data);
	else
	{
		while (1)
		{
			if (is_true(philo->data))
				break ;
			if (philo->has_eaten == 0)
				eat_routine(philo);
			else
			{
				sleep_think(philo);
				philo->has_eaten = 0;
			}
		}
	}
	return (NULL);
}

void	onephilo(t_data *data)
{
	pthread_mutex_lock(data->fork);
	print_log(data->philo, get_time(), FORK);
}
