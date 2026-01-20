/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 06:24:09 by dbouizem          #+#    #+#             */
/*   Updated: 2025/09/23 17:30:40 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_utoa_base(unsigned int n, const char *base)
{
	static char	buffer[35];
	int			base_len;
	int			bufsize;
	int			i;

	bufsize = sizeof(buffer);
	base_len = ft_strlen(base);
	i = bufsize - 1;
	buffer[i--] = '\0';
	if (n == 0)
	{
		buffer[i] = base[0];
		return (&buffer[i]);
	}
	while (n > 0 && i >= 0)
	{
		buffer[i--] = base[n % base_len];
		n /= base_len;
	}
	return (&buffer[i + 1]);
}

void	ft_print_u_int(unsigned int n, t_printf *data)
{
	char	*str;

	str = ft_utoa_base(n, DIGITS);
	if (!str)
	{
		data->error = 1;
		return ;
	}
	ft_print_str(str, data);
}
