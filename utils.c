/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dravaono <dravaono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 20:03:27 by dravaono          #+#    #+#             */
/*   Updated: 2024/06/27 20:01:11 by dravaono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		s;
	long	r;

	i = 0;
	r = 0;
	s = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = s * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + str[i] - '0';
		i++;
	}
	if ((r * s) > INT_MAX || (r * s) < INT_MIN)
		return (-1);
	return (r * s);
}

int	is_true(t_data *data)
{
	pthread_mutex_lock(&data->istrue);
	if (data->die == true)
	{
		pthread_mutex_unlock(&data->istrue);
		return (1);
	}
	if (data->full == true)
	{
		pthread_mutex_unlock(&data->istrue);
		return (2);
	}
	pthread_mutex_unlock(&data->istrue);
	return (0);
}

int	print_log(t_philo *philo, long long time_pass, int flg)
{
	long long	time;

	(void)time_pass;
	pthread_mutex_lock(&philo->data->print);
	time = get_time() - philo->data->start;
	if (is_true(philo->data))
	{
		if (flg == DIE)
			printf("%lld %d died\n", time, philo->philo_number);
		else if (flg == FULL)
			printf("everyone eated\n");
	}
	else if (flg == EAT)
		printf("%lld %d is eating\n", time, philo->philo_number);
	else if (flg == SLEEP)
		printf("%lld %d is sleeping\n", time, philo->philo_number);
	else if (flg == THINK)
		printf("%lld %d is thinking\n", time, philo->philo_number);
	else if (flg == FORK)
		printf("%lld %d has taken a fork\n", time, philo->philo_number);
	pthread_mutex_unlock(&philo->data->print);
	return (0);
}
