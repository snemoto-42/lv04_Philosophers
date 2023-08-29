/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_check_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:24:27 by snemoto           #+#    #+#             */
/*   Updated: 2023/08/27 14:57:51 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

static bool	ph_is_invalid(int argc, char **argv)
{
	int		i;
	size_t	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (ft_strchr(NUM, argv[i][j]) == NULL)
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

bool	ph_check_arg(int argc, char **argv)
{
	if (!(argc == 5 || argc == 6))
	{
		printf("error in num_argc\n");
		return (true);
	}
	if (ph_is_invalid(argc, argv))
	{
		printf("error in invalid_arg\n");
		return (true);
	}
	if (ft_atoi(argv[1]) < 1)
	{
		printf("error in num_philo\n");
		return (true);
	}
	return (false);
}
