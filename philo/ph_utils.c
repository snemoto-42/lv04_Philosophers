/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 09:46:19 by snemoto           #+#    #+#             */
/*   Updated: 2023/08/29 13:05:39 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;
	long			msec;

	if (gettimeofday(&tv, NULL) != 0)
		return (0);
	msec = tv.tv_sec * 1000;
	msec += tv.tv_usec / 1000;
	return (msec);
}

void	ph_print(t_philo *philo)
{
	long	time;
	size_t	idx;

	time = get_time() - philo->start_time;
	idx = 1 + philo->index;
	if (philo->act == PH_SLEEP)
		printf("%10ld %zu is sleeping\n", time, idx);
	else if (philo->act == PH_EAT)
		printf("%10ld %zu is eating\n", time, idx);
	else if (philo->act == PH_THINK)
		printf("%10ld %zu is thinking\n", time, idx);
	else if (philo->act == PH_TAKE)
		printf("%10ld %zu has taken a fork\n", time, idx);
	else if (philo->act == PH_DEAD)
		printf("%10ld %zu died\n", time, idx);
	return ;
}
