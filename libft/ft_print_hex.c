/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 05:04:14 by dbouizem          #+#    #+#             */
/*   Updated: 2025/09/23 17:30:23 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_hex(unsigned int n, int uppercase, t_printf *data)
{
	const char	*base;
	char		buffer[20];
	int			i;

	if (data->error)
		return ;
	i = sizeof(buffer) - 1;
	buffer[i] = '\0';
	if (uppercase)
		base = HEXUPP;
	else
		base = HEXLOW;
	if (n == 0)
		buffer[--i] = '0';
	while (n > 0 && i > 0)
	{
		buffer[--i] = base[n % 16];
		n /= 16;
	}
	ft_print_str(&buffer[i], data);
}
