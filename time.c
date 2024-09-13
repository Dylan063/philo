/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dravaono <dravaono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 20:17:01 by dravaono          #+#    #+#             */
/*   Updated: 2024/06/27 19:55:54 by dravaono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_time(void)
{
	struct timeval	t;
	long long		time;

	if (gettimeofday(&t, NULL) == -1)
		return (write(2, "Get_time Error\n", 16));
	time = (t.tv_sec * 1e3) + (t.tv_usec * 1e-3);
	return (time);
}

void	spin_sleep(size_t ms, t_data *data)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < ms && !is_true(data))
		usleep(500);
}

int	unclock_eat(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->fork[philo->fork_left]);
	pthread_mutex_unlock(&philo->data->fork[philo->fork_right]);
	return (0);
}
