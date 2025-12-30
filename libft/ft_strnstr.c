/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:20:14 by dbouizem          #+#    #+#             */
/*   Updated: 2025/12/30 08:32:26 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
