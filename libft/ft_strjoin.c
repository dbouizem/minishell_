/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 03:57:30 by dbouizem          #+#    #+#             */
/*   Updated: 2025/12/30 08:31:27 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
