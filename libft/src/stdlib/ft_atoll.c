/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 00:08:41 by dbouizem          #+#    #+#             */
/*   Updated: 2025/12/05 09:30:41 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_overflow(long long r, char digit, int *overflow)
{
	if (r > (9223372036854775807LL - (digit - '0')) / 10)
	{
		*overflow = 1;
		return (1);
	}
	return (0);
}

long long	ft_atoll(const char *str, int *overflow)
{
	long long	r;
	int			s;

	r = 0;
	s = 1;
	*overflow = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			s = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (check_overflow(r, *str, overflow))
			return (0);
		r = r * 10 + (*str - '0');
		str++;
	}
	return (r * s);
}
