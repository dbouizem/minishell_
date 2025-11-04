/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:14:12 by dbouizem          #+#    #+#             */
/*   Updated: 2024/12/24 22:39:37 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_memcpy - copie n octets de la zone mémoire src vers la zone memoire dst.
*/

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*cdest;
	unsigned char	*csrc;

	if (!dest && !src)
		return (dest);
	cdest = (unsigned char *)dest;
	csrc = (unsigned char *)src;
	while (n--)
		*cdest++ = *csrc++;
	return (dest);
}
/*
int main() {
	char *src = "Testting ft_memcpy";
	char dest[20];

	ft_memcpy(dest, src, 5);
	dest[5] = '\0';
	printf("Source: %s\n", src);
	printf("Destination: %s\n", dest);
	return 0;
}*/
