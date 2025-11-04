/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:24:55 by dbouizem          #+#    #+#             */
/*   Updated: 2024/12/22 08:02:50 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_strlcat - ajoute la chaîne src à la fin de la chaîne dest,en garantissant
** que le résultat est toujours terminé par un caractère nul '\0'.
*/

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	lend;
	size_t	lens;
	size_t	i;
	size_t	j;

	lend = ft_strlen(dest);
	lens = ft_strlen(src);
	i = 0;
	j = lend;
	if (n == 0)
		return (lens);
	if (lend > n)
		return (n + lens);
	while (src[i] && j < n - 1)
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (lend + lens);
}
/*
int	main()
{
	char	dst[30] = "Testting ";
	char	*src = "ft_strlcat";
	size_t	result;

	result = ft_strlcat(dst, src, 30);
	printf("dst: %s\n", dst);
	printf("returned: %zu\n", result);
	return (0);
}*/
