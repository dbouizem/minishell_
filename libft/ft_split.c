/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 04:25:38 by dbouizem          #+#    #+#             */
/*   Updated: 2025/12/30 08:31:07 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
