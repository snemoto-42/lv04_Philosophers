/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:22:34 by snemoto           #+#    #+#             */
/*   Updated: 2023/08/28 18:43:43 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define NUM "1234567890"

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_info
{
	size_t	num_philo;
	long	time_die;
	long	time_eat;
	long	time_sleep;
	size_t	num_must_eat;
	bool	finish;
}	t_info;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}	t_fork;

typedef enum e_philo_action
{
	PH_SLEEP,
	PH_EAT,
	PH_THINK,
	PH_TAKE,
	PH_DEAD,
}	t_philo_action;

typedef struct s_philo
{
	size_t			index;
	size_t			num_eat;
	long			previous_eat_time;
	long			start_time;
	t_fork			*left;
	t_fork			*right;
	t_info			*info;
	t_philo_action	act;
	pthread_t		tid;
	pthread_t		tid_m;
}	t_philo;

bool	ph_check_arg(int argc, char **argv);

int		ft_atoi(const char *str);
t_info	*init_info(int argc, char **argv);

t_fork	*init_forks(t_info *info);
t_philo	**init_philos(t_info *info, t_fork *forks);

long	get_time(void);
void	ph_print(t_philo *philo);

bool	th_create(t_philo *philo);

#endif
