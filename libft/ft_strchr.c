/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:50:56 by dbouizem          #+#    #+#             */
/*   Updated: 2024/12/22 07:53:13 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_strchr - localise la première occurrence d'un caractère dans une chaîne.
*/

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (char)c)
		s++;
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}
/*
int	main()
{
	char *src = "Coucou";
	int c = 'o';
	char *result = ft_strchr(src, c);
	printf("result: %s", result);
	return (0);
}*/
