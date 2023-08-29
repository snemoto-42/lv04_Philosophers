/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:24:27 by snemoto           #+#    #+#             */
/*   Updated: 2023/08/28 17:07:59 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_flow(long sum, char c, int flag)
{
	if (LONG_MAX / 10 < sum && c && flag == 0)
		return (1);
	if (sum == LONG_MAX / 10 && LONG_MAX % 10 < c - '0' && flag == 0)
		return (1);
	if (LONG_MIN / 10 > -sum && c && flag == 1)
		return (-1);
	if (LONG_MIN / 10 == -sum && LONG_MIN % 10 > -(c - '0') && flag == 1)
		return (-1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		flag;
	long	sum;

	flag = 0;
	sum = 0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			flag = 1;
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		sum = sum * 10 + (*str - '0');
		str++;
		if (check_flow(sum, *str, flag) > 0)
			return ((int)LONG_MAX);
		if (check_flow(sum, *str, flag) < 0)
			return ((int)LONG_MIN);
	}
	if (flag == 1)
		sum *= -1;
	return ((int)sum);
}

t_info	*init_info(int argc, char **argv)
{
	t_info	*info;

	info = (t_info *)malloc(sizeof(t_info) * (argc - 1));
	if (info == NULL)
	{
		printf("error in malloc\n");
		return (NULL);
	}
	info->num_philo = ft_atoi(argv[1]);
	info->time_die = ft_atoi(argv[2]);
	info->time_eat = ft_atoi(argv[3]);
	info->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->num_must_eat = ft_atoi(argv[5]);
	info->finish = false;
	return (info);
}
