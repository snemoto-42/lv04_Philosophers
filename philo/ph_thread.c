/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:24:27 by snemoto           #+#    #+#             */
/*   Updated: 2023/08/29 12:21:13 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	pick_up_fork(t_philo *philo)
{
	if (philo->info->finish)
		return (true);
	pthread_mutex_lock(&(philo->left->mutex));
	if (philo->info->finish)
		return (true);
	pthread_mutex_lock(&(philo->right->mutex));
	if (philo->info->finish)
		return (true);
	philo->act = PH_TAKE;
	ph_print(philo);
	return (false);
}

static bool	th_eat(t_philo *philo)
{
	if (philo->info->finish)
		return (true);
	philo->act = PH_EAT;
	philo->previous_eat_time = get_time();
	philo->num_eat++;
	ph_print(philo);
	usleep(philo->info->time_eat * 1000);
	pthread_mutex_unlock(&(philo->left->mutex));
	pthread_mutex_unlock(&(philo->right->mutex));
	return (false);
}

static void	*th_action(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->index % 2)
		usleep(5 * 1000);
	while (1)
	{
		if (philo->info->finish)
			return (NULL);
		philo->act = PH_THINK;
		ph_print(philo);
		if (philo->info->finish)
			return (NULL);
		if (pick_up_fork(philo))
			return (NULL);
		if (th_eat(philo))
			return (NULL);
		if (philo->info->finish)
			return (NULL);
		philo->act = PH_SLEEP;
		ph_print(philo);
		usleep(philo->info->time_sleep * 1000);
	}
}

static void	*th_check(void *arg)
{
	t_philo	*philo;
	long	time_diff;

	philo = (t_philo *)arg;
	while (1)
	{
		time_diff = get_time() - philo->previous_eat_time;
		if (time_diff < 0)
			;
		else if (time_diff > philo->info->time_die)
		{
			if (philo->info->finish)
				return (NULL);
			philo->info->finish = true;
			philo->act = PH_DEAD;
			ph_print(philo);
			return (NULL);
		}
		else if (philo->num_eat == philo->info->num_must_eat)
		{
			philo->info->finish = true;
			return (NULL);
		}
	}
	return (NULL);
}

bool	th_create(t_philo *philo)
{
	pthread_t	tid;
	pthread_t	tid_m;

	philo->start_time = get_time();
	philo->previous_eat_time = philo->start_time;
	if (pthread_create(&tid, NULL, th_action, philo) != 0)
		return (true);
	philo->tid = tid;
	if (pthread_create(&tid_m, NULL, th_check, philo) != 0)
		return (true);
	philo->tid_m = tid_m;
	return (false);
}
