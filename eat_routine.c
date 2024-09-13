/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_routine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dravaono <dravaono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 20:13:52 by dravaono          #+#    #+#             */
/*   Updated: 2024/06/27 19:51:39 by dravaono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	eat_routine(t_philo *philo)
{
	if (is_true(philo->data))
		return (1);
	if (philo->fork_left < philo->fork_right)
		pick_right(philo);
	else
		pick_left(philo);
	eat_now(philo);
	unclock_eat(philo);
	return (0);
}

void	pick_right(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->fork_right]);
	print_log(philo, get_time(), FORK);
	pthread_mutex_lock(&philo->data->fork[philo->fork_left]);
	print_log(philo, get_time(), FORK);
}

void	pick_left(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->fork_left]);
	print_log(philo, get_time(), FORK);
	pthread_mutex_lock(&philo->data->fork[philo->fork_right]);
	print_log(philo, get_time(), FORK);
}

int	eat_now(t_philo *philo)
{
	if (is_true(philo->data))
		return (1);
	print_log(philo, get_time(), EAT);
	pthread_mutex_lock(&philo->data->ubereats);
	philo->ubereats++;
	if (philo->ubereats >= philo->data->nb_eat)
	{
		pthread_mutex_lock(&philo->data->fulltruetwo);
		philo->full = true;
		pthread_mutex_unlock(&philo->data->fulltruetwo);
	}
	pthread_mutex_unlock(&philo->data->ubereats);
	pthread_mutex_lock(&philo->data->eat_rout);
	philo->has_eaten = 1;
	pthread_mutex_unlock(&philo->data->eat_rout);
	pthread_mutex_lock(&philo->data->time_eatnow);
	philo->last_time_to_eat = get_time();
	pthread_mutex_unlock(&philo->data->time_eatnow);
	spin_sleep(philo->data->time_to_eat, philo->data);
	return (0);
}

void	sleep_think(t_philo *philo)
{
	if (is_true(philo->data))
		return ;
	print_log(philo, get_time(), SLEEP);
	spin_sleep(philo->data->time_to_sleep, philo->data);
	print_log(philo, get_time(), THINK);
	usleep(100);
}
