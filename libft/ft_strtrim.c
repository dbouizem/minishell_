/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 05:34:51 by dbouizem          #+#    #+#             */
/*   Updated: 2025/04/25 03:33:17 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_strtrim - éliminer les espaces (ou d'autres caractères spécifiques)
** au début et à la fin d'une chaîne de caractères.
**
** Compilation: gcc -Wall -Wextra -Werror ft_strtrim.c ft_strlen.c ft_strchr.c
** ft_substr.c ft_strdup.c ft_calloc.c ft_memmove.c ft_memcpy.c ft_memset.c
*/

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	i = ft_strlen(s1);
	while (i && ft_strchr(set, s1[i]))
		i--;
	return (ft_substr(s1, 0, i + 1));
}
/*int	main()
{
	char	*str = " / Testting my function  . ";
	char	*set = " ./";
	char	*rslt;
	printf("str: %s\n", str);
	rslt = ft_strtrim(str, set);
	if (rslt)
	{
		printf("rslt: %s\n", rslt);
		free(rslt);
	}
	else
		printf("Error\n");

	return (0);
}*/
