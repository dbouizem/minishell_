/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 01:04:14 by dbouizem          #+#    #+#             */
/*   Updated: 2025/01/22 20:19:49 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_memchar - recherche la première occurrence d'un caractère dans
** une zone memoire
*/

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
/*
int	main()
{
	const char *str = "Bonjour, Loli!";
	char *result = ft_memchr(str, 'r', 15);
	if (result)
		printf("\"%s\" trouve a la position: %ld\n", result, result - str);
	else
		printf("Caractere non trouve.");
	return 0;
}*/
