/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:59:20 by dbouizem          #+#    #+#             */
/*   Updated: 2024/12/22 07:36:19 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_strrchr - Localise la dernière occurrence d'un caractère dans une chaîne.
**
** Compilation: gcc -Wall -Wextra -Werror ft_strrchr.c ft_strlen.c
*/

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i--;
	}
	return (NULL);
}
/*
int	main()
{
	char *src = "Testting strrchr";
	char c = 'i';
	char *result = ft_strrchr(src, c);
	printf("result: %s", result);
	return (0);
}*/
