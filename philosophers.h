/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dravaono <dravaono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:51:27 by dravaono          #+#    #+#             */
/*   Updated: 2024/06/27 19:55:31 by dravaono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define DIE 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define FORK 4
# define FULL 5

typedef struct s_philo
{
	bool			full;
	int				ubereats;
	int				has_eaten;
	int				philo_number;
	int				last_time_to_eat;
	int				fork_right;
	int				fork_left;
	int				status_dead;
	struct s_data	*data;
	pthread_t		thread;
}					t_philo;

typedef struct s_data
{
	pthread_t		superviseurdie;
	pthread_t		superviseureat;
	bool			die;
	bool			full;
	long long		start;
	int				philo_is_die;
	int				time_to_die;
	int				time_to_sleep;
	int				nb_eat;
	int				num_philo;
	int				time_to_eat;
	int				j;
	int				count;
	pthread_mutex_t	eat_rout;
	pthread_mutex_t	check_die;
	pthread_mutex_t	lock_die;
	pthread_mutex_t	time_eatnow;
	pthread_mutex_t	time_eatcheckdie;
	pthread_mutex_t	print;
	pthread_mutex_t	ubereats;
	pthread_mutex_t	isfull;
	pthread_mutex_t	istrue;
	pthread_mutex_t	fulltrue;
	pthread_mutex_t	fulltruetwo;
	pthread_mutex_t	*fork;
	struct s_philo	*philo;
}					t_data;

int					ft_atoi(const char *str);
void				util(char **str, t_data *data);
void				*routine(void *ptr);
void				init_philo(t_data *data);
int					eat_routine(t_philo *philo);
int					fork_left(t_philo *philo);
int					fork_right(t_philo *philo);
int					drop_fork(t_philo *philo);
void				*check_die(void *ptr);
void				spin_sleep(size_t ms, t_data *data);
long long			get_time(void);
int					print_log(t_philo *philo, long long time_pass, int flg);
void				sleep_think(t_philo *philo);
void				all_mutex(t_data *data);
void				onephilo(t_data *data);
void				time_to_die(t_data *data);
void				pick_right(t_philo *philo);
void				pick_left(t_philo *philo);
int					eat_now(t_philo *philo);
int					unclock_eat(t_philo *philo);
int					is_true(t_data *data);
int					print_die(t_philo *philo, int flg);
int					check_onedie(t_data *data);
int					check_eat(t_data *data);
void				joinfinish(t_data *data);
void				fulltrue(t_data *data);

#endif