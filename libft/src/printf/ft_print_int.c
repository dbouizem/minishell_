/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:29:12 by dbouizem          #+#    #+#             */
/*   Updated: 2025/09/23 17:30:28 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*convert_positive(long nb, char *buffer, int i)
{
	while (nb > 0)
	{
		buffer[i--] = (nb % 10) + '0';
		nb /= 10;
	}
	return (&buffer[i + 1]);
}

static char	*convert_negative(long nb, char *buffer, int i)
{
	nb = -nb;
	while (nb > 0)
	{
		buffer[i--] = (nb % 10) + '0';
		nb /= 10;
	}
	buffer[i--] = '-';
	return (&buffer[i + 1]);
}

char	*ft_itoa(int n)
{
	static char	buffer[12];
	int			i;
	long		nb;

	nb = n;
	i = 11;
	buffer[i--] = '\0';
	if (nb == 0)
	{
		buffer[i] = '0';
		return (&buffer[i]);
	}
	if (nb < 0)
		return (convert_negative(nb, buffer, i));
	else
		return (convert_positive(nb, buffer, i));
}

void	ft_print_int(int n, t_printf *data)
{
	char	*str;

	str = ft_itoa(n);
	if (!str || data->error)
	{
		data->error = 1;
		return ;
	}
	ft_print_str(str, data);
}
