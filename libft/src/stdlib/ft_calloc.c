/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 00:39:10 by dbouizem          #+#    #+#             */
/*   Updated: 2025/12/30 08:29:22 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*alloc;
	size_t	tot_size;

	if (num == 0 || size == 0)
		return (malloc(0));
	tot_size = num * size;
	if (tot_size / num != size)
		return (NULL);
	alloc = malloc(tot_size);
	if (!(alloc))
		return (NULL);
	ft_memset(alloc, 0, tot_size);
	return (alloc);
}
