/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:24:27 by snemoto           #+#    #+#             */
/*   Updated: 2023/08/29 13:14:46 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_var(t_info *info, t_fork *forks)
{
	if (info == NULL)
		;
	else if (forks == NULL)
		free(info);
	else
	{
		free(info);
		free(forks);
	}
}

static void	ph_destroy(t_info *info, t_fork *forks, t_philo **philos)
{
	size_t	idx;

	idx = 0;
	while (idx < info->num_philo)
	{
		pthread_mutex_destroy(&(forks[idx].mutex));
		free(philos[idx]);
		idx++;
	}
	free(forks);
	free(philos);
	free(info);
}

static void	ph_philo_one(t_philo *philo)
{
	philo->start_time = get_time();
	philo->previous_eat_time = philo->start_time;
	philo->act = PH_TAKE;
	ph_print(philo);
	usleep(philo->info->time_die * 1000);
	philo->act = PH_DEAD;
	ph_print(philo);
	philo->info->finish = true;
}

static void	ph_thread(t_info *info, t_philo **philos)
{
	size_t	idx;

	idx = 0;
	if (info->num_philo == 1)
	{
		ph_philo_one(philos[idx]);
		return ;
	}
	while (idx < info->num_philo)
		if (th_create(philos[idx++]))
			return ;
	idx = 0;
	while (idx < info->num_philo)
		if (pthread_detach(philos[idx++]->tid_m) != 0)
			return ;
	idx = 0;
	while (idx < info->num_philo)
		if (pthread_detach(philos[idx++]->tid) != 0)
			return ;
}

int	main(int argc, char **argv)
{
	t_info	*info;
	t_fork	*forks;
	t_philo	**philos;

	if (ph_check_arg(argc, argv))
		return (0);
	info = init_info(argc, argv);
	forks = init_forks(info);
	if (forks == NULL)
	{
		free_var(info, forks);
		return (0);
	}
	philos = init_philos(info, forks);
	if (philos == NULL)
	{
		free_var(info, forks);
		return (0);
	}
	ph_thread(info, philos);
	while (!info->finish)
		;
	ph_destroy(info, forks, philos);
	return (0);
}
