/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:20:14 by dbouizem          #+#    #+#             */
/*   Updated: 2025/04/23 17:20:13 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_strnstr - localise la première occurrence du message terminé
** par un caractère nul.
*/

#include "libft.h"

char	*ft_strnstr(const char *h, const char *n, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*n)
		return ((char *)h);
	i = 0;
	while (h[i] && i < len)
	{
		j = 0;
		if (h[i] == n[0])
		{
			while (n[j] && h[i + j] && (i + j) < len && h[i + j] == n[j])
				j++;
			if (n[j] == '\0')
				return ((char *)&h[i]);
		}
		i++;
	}
	return (NULL);
}
/*
int	main()
{
	char	str[] = "Bonjour Laure !";
	char	to_find[] = "Laure";

	char	*result = ft_strnstr(str, to_find, 20);
	if (result)
		printf("Le mot a trouver se trouve ici : %s\n", result);
	else
		printf("Le mot n'a pas ete trouve.\n");
	return(0);
}*/
