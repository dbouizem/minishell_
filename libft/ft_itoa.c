/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 01:28:25 by dbouizem          #+#    #+#             */
/*   Updated: 2025/12/30 08:29:49 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digit(int n)
{
	int	count;

	if (n <= 0)
		count = 1;
	else
		count = 0;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static void	ft_putnbr(long num, char *result, int len)
{
	while (num > 0)
	{
		result[--len] = (num % 10) + '0';
		num /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*result;
	int		len;
	long	num;

	num = (long)n;
	len = ft_count_digit(n);
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (num == 0)
		result[0] = '0';
	else if (num < 0)
	{
		result[0] = '-';
		num = -num;
	}
	ft_putnbr(num, result, len);
	return (result);
}
