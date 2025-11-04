/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 00:08:41 by dbouizem          #+#    #+#             */
/*   Updated: 2024/12/24 22:51:15 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_atoi - convertit la chaîne ASCII en entier.
*/

#include "libft.h"

static int	ft_isspace(char c)
{
	return (c == ' ' || c == '\n'
		||c == '\t' || c == '\v' || c == '\f' || c == '\r');
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (ft_isdigit(*str))
		result = (result * 10) + (*str++ - '0');
	return (result * sign);
}
/*
int main()
{
	printf("Result: %d\n", ft_atoi("-42"));
	printf("Result: %d\n", ft_atoi("+4193 with words"));
	printf("Result: %d\n", ft_atoi("words 42"));
	printf("Result: %d\n", ft_atoi("  123"));
	printf("Result: %d\n", ft_atoi("0"));
	printf("Result: %d\n", ft_atoi(NULL));
	return 0;
}*/
