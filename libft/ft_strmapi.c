/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 15:36:09 by dbouizem          #+#    #+#             */
/*   Updated: 2025/04/25 03:33:47 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_strmapi - applique une fonction à chaque caractère d'une chaîne
** en tenant compte de sa position.
** Retourne une nouvelle chaîne
**
** Complation: gcc -Wall -Wextra -Werror ft_strmapi.c ft_toupper.c ft_strlen.c
*/

#include "libft.h"

/*char	apply_toupper(unsigned int i, char c)
{
	(void)i;
	return (ft_toupper(c));
}*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*result;
	size_t	len;
	size_t	i;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = f((unsigned int)i, s[i]);
		i++;
	}
	result[len] = '\0';
	return (result);
}
/*int	main(void)
{
	char	*str = "abcd";
	char	*result = ft_strmapi(str, apply_toupper);
	printf("Original string: \"%s\"\n", str);
	if (result)
	{
		printf("Transformed string: \"%s\"\n", result);
		free(result);
	}
	else
		printf("Error: ft_strmapi returned NULL.\n");
	return (0);
}*/
