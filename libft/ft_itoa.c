/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 01:28:25 by dbouizem          #+#    #+#             */
/*   Updated: 2025/04/24 01:10:25 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_itoa - convertit un entier en chaîne de caractères.
*/

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
/*
int	main(void)
{
	int		n = 1999;
	char	*rslt = ft_itoa(n);
	if (rslt)
	{
		printf("result: %s",rslt);
		free(rslt);
	}
	else
		printf("ERROR !!!");
	return (0);
}*/
