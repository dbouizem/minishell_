/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:02:17 by dbouizem          #+#    #+#             */
/*   Updated: 2025/12/30 08:30:28 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, void *src, size_t n)
{
	unsigned char	*cdest;
	unsigned char	*csrc;

	if (!dest && !src)
		return (dest);
	cdest = (unsigned char *) dest;
	csrc = (unsigned char *) src;
	if (cdest > csrc && cdest < csrc + n)
	{
		cdest += n;
		csrc += n;
		while (n--)
			*--cdest = *--csrc;
	}
	else
		ft_memcpy(cdest, csrc, n);
	return (dest);
}
