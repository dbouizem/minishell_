/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:46:25 by dbouizem          #+#    #+#             */
/*   Updated: 2024/12/22 07:35:19 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_strlcpy - copie une chaîne avec sécurité de taille.
**
** Compilatin: gcc -Wall -Wextra -Werror ft_strlcpy.c ft_strlen.c
*/

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen(src);
	if (!dest || !src)
		return (0);
	if (size == 0)
		return (src_len);
	while (src[i] && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_len);
}
/*int	main()
{
	char dest[15];
	char *src = "Testting ft_strlcpy";
	size_t len;

	len = ft_strlcpy(dest, src, 15);
	printf("src: %s\n", src);
	printf("dest: %s\n", dest);
	printf("len: %zu\n", len);
	return (0);
}*/
