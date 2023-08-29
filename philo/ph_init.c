/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:24:27 by snemoto           #+#    #+#             */
/*   Updated: 2023/08/29 12:04:47 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_fork(t_fork *fork)
{
	pthread_mutex_init(&fork->mutex, NULL);
}

t_fork	*init_forks(t_info *info)
{
	t_fork	*forks;
	size_t	idx;

	if (info == NULL)
		return (NULL);
	forks = (t_fork *)malloc(sizeof(t_fork) * info->num_philo);
	if (forks == NULL)
	{
		printf("error in malloc\n");
		return (NULL);
	}
	idx = 0;
	while (idx < info->num_philo)
	{
		init_fork(&forks[idx]);
		idx++;
	}
	return (forks);
}

static void	init_philo(t_philo *philo, size_t idx, t_fork *left, t_fork *right)
{
	philo->index = idx;
	philo->left = left;
	philo->right = right;
	philo->num_eat = 0;
}

static void	free_array(t_philo **philos, size_t len)
{
	size_t	idx;

	idx = 0;
	while (idx < len)
	{
		free(philos[idx]);
		idx++;
	}
	free(philos);
}

t_philo	**init_philos(t_info *info, t_fork *forks)
{
	t_philo	**philos;
	size_t	idx;

	philos = (t_philo **)malloc(sizeof(t_philo *) * info->num_philo);
	if (philos == NULL)
	{
		printf("error in malloc\n");
		return (NULL);
	}
	idx = 0;
	while (idx < info->num_philo)
	{
		philos[idx] = (t_philo *)malloc(sizeof(t_philo));
		if (philos[idx] == NULL)
		{
			printf("error in malloc\n");
			free_array(philos, idx);
			return (NULL);
		}
		philos[idx]->info = info;
		init_philo(philos[idx], idx, \
			&forks[idx], &forks[(idx + 1) % info->num_philo]);
		idx++;
	}
	return (philos);
}
