/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 00:40:06 by dbouizem          #+#    #+#             */
/*   Updated: 2024/12/22 07:19:56 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_strdup - duplique une chaîne de caractères.
**
** Compilation: gcc -Wall -Wextra -Werror ft_calloc.c ft_memcpy.c
** ft_strdup.c ft_memset.c ft_strlen.c
*/
#include "libft.h"

char	*ft_strdup(const char *src)
{
	size_t	len;
	char	*copy;

	len = ft_strlen(src) + 1;
	copy = ft_calloc(len, sizeof(char));
	if (!copy)
		return (NULL);
	ft_memcpy(copy, src, len);
	return (copy);
}
/*
int	main()
{
	char	*str = "Testting strdup";
	char	*dup;

	dup = ft_strdup(str);
	if (!dup)
	{
		printf("Erorr");
		return (1);
	}
	printf("str: %s\n", str);
	printf("dup; %s\n", dup);
	free(dup);
	return (0);

}*/
