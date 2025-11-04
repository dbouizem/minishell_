/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 03:57:30 by dbouizem          #+#    #+#             */
/*   Updated: 2024/12/22 07:34:08 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_strjoin - concaténer deux chaînes de caractères.
**
** Compilation: gcc -Wall -Wextra -Werror ft_strjoin.c
** ft_strlen.c ft_calloc.c ft_strlcpy.c ft_strlcat.c ft_memset.c
*/

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*rslt;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	rslt = ft_calloc(len + 1, sizeof(char));
	if (!rslt)
		return (NULL);
	ft_strlcpy(rslt, s1, len + 1);
	ft_strlcat(rslt, s2, len + 1);
	return (rslt);
}
/*int	main()
{
	char	*s1 = "Testting ";
	char	*s2 = "my function.";
	
	//char    *s2 = NULL;
	//char    *s2 = "";
	char	*r = ft_strjoin(s1, s2);
	if (r)
		printf("r = %s\n", r);
	else
		printf("Error\n");
	return (0);
}*/
