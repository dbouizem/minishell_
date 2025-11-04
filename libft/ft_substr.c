/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 01:37:46 by dbouizem          #+#    #+#             */
/*   Updated: 2024/12/22 07:12:50 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_substr - extraire une sous-chaîne d'une chaîne donnée (s).
**
** Compilation: gcc -Wall -Wextra -Werror ft_substr.c ft_strdup.c
** ft_strlen.c ft_calloc.c ft_memmove.c ft_memcpy.c ft_memset.c
*/

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	len_s;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (start >= len_s)
		return (ft_strdup(""));
	if (len > (len_s - start))
		len = len_s - start;
	dst = ft_calloc(len + 1, sizeof(char));
	if (!dst)
		return (NULL);
	ft_memmove(dst, (void *)(s + start), len);
	dst[len] = '\0';
	return (dst);
}
/*
int	main(void)
{
	char	*result;

	result = ft_substr("Hello World!", 6, 5);
	if (result)
	{
		printf("Sous-chaîne extraite : %s\n", result);
		free(result);
	}
	result = ft_substr("Hello World!", 12, 5);
	if (result)
	{
		printf("Sous-chaîne extraite : %s\n", result);
		free(result);
	}
	return (0);
}*/
