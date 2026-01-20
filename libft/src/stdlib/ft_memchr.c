/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 01:04:14 by dbouizem          #+#    #+#             */
/*   Updated: 2025/12/30 08:30:18 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	cc;

	cc = (unsigned char) c;
	ptr = (unsigned char *) s;
	while (n--)
	{
		if (*ptr == cc)
			return ((void *)ptr);
		ptr++;
	}
	return (NULL);
}
