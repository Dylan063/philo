/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dravaono <dravaono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:59:07 by dravaono          #+#    #+#             */
/*   Updated: 2024/06/27 19:52:48 by dravaono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	firstpars(char **pars)
{
	int	i;
	int	j;

	j = 1;
	while (pars[j])
	{
		i = 0;
		if (pars[j][0] == '0' && pars[j][1] == '\0')
			return (1);
		while (pars[j][i])
		{
			if (!(pars[j][i] >= '0' && pars[j][i] <= '9'))
				return (1);
			i++;
		}
		j++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		return (1);
	if (firstpars(av) == 1)
		return (1);
	data.die = false;
	data.full = false;
	util(av, &data);
	while (1)
	{
		if (is_true(&data) == 1)
		{
			print_log(data.philo, get_time(), DIE);
			break ;
		}
		if (is_true(&data) == 2)
		{
			print_log(data.philo, get_time(), FULL);
			break ;
		}
		usleep(500);
	}
	joinfinish(&data);
	return (0);
}

void	joinfinish(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philo)
		pthread_join(data->philo[i].thread, NULL);
	pthread_join(data->superviseurdie, NULL);
}
