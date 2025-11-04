/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 04:25:38 by dbouizem          #+#    #+#             */
/*   Updated: 2024/12/24 18:10:08 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_split - découper une chaîne de caractères en un tableau de sous-chaînes.
**
** Compilation: gcc -Wall -Wextra -Werror ft_split.c ft_calloc.c
** ft_substr.c ft_memset.c ft_strlen.c ft_strdup.c ft_memmove.c ft_memcpy.c
*/

#include "libft.h"

static	int	ft_count_word(char const *s, char c)
{
	size_t	count;
	int		word;

	count = 0;
	word = 0;
	while (*s)
	{
		if (*s != c && word == 0)
		{
			count++;
			word = 1;
		}
		else if (*s == c)
			word = 0;
		s++;
	}
	return (count);
}

static char	**ft_free_all(char **array, size_t i)
{
	while (i > 0)
		free(array[--i]);
	free(array);
	return (NULL);
}

static char	**ft_fill_word(char **array, const char *s, char c)
{
	const char	*start;
	size_t		i;
	size_t		len;

	start = NULL;
	i = 0;
	while (*s)
	{
		if (*s != c && start == NULL)
			start = s;
		if ((*s == c || *(s + 1) == '\0') && start != NULL)
		{
			len = s - start + (*s != c && (*(s + 1) == '\0'));
			array[i] = ft_substr(start, 0, len);
			if (!array[i])
				return (ft_free_all(array, i));
			i++;
			start = NULL;
		}
		s++;
	}
	array[i] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	size_t		count;
	char		**array;

	if (!s)
		return (NULL);
	count = ft_count_word(s, c);
	array = ft_calloc(count + 1, sizeof(char *));
	if (!array)
		return (NULL);
	if (!ft_fill_word(array, s, c))
		return (NULL);
	return (array);
}
/*
int	main()
{
	char	**result;
	size_t	i;

	result = ft_split("ggloirem miod non, mi.", 'i');
	if (!result)
	{
		printf("NULL\n");
		return (1);
	}
	i = 0;
	while (result[i])
	{
		printf("word %zu: %s\n",i , result[i]);
		free(result[i]);
		i++;
	}
	free(result);
}*/
