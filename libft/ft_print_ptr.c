/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 04:03:41 by dbouizem          #+#    #+#             */
/*   Updated: 2025/09/23 17:30:32 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_utoa(uintptr_t n, const char *base)
{
	static char	buffer[20];
	int			base_len;
	int			bufsize;
	int			i;

	bufsize = sizeof(buffer);
	base_len = ft_strlen(base);
	i = bufsize - 1;
	buffer[i--] = '\0';
	if (n == 0)
		buffer[i] = base[0];
	while (n > 0 && i >= 0)
	{
		buffer[i--] = base[n % base_len];
		n /= base_len;
	}
	return (&buffer[i + 1]);
}

void	ft_print_ptr(void *ptr, t_printf *data)
{
	uintptr_t	address;
	char		*str;

	address = (uintptr_t)ptr;
	if (address == 0)
	{
		ft_print_str("(nil)", data);
		return ;
	}
	str = ft_utoa(address, HEXLOW);
	ft_print_str("0x", data);
	ft_print_str(str, data);
}
